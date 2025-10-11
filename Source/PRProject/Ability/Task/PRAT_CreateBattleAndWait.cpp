// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Task/PRAT_CreateBattleAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LevelStreamingDynamic.h"
#include "Engine/StreamableManager.h"
#include "Engine/LevelStreamingDynamic.h"
#include "Data/PRBattleDataAsset.h"
#include "PaperZDCharacter.h"
#include "Battle/PRBattleLevelManager.h"
#include "Character/PRCharacterBase.h"

UPRAT_CreateBattleAndWait* UPRAT_CreateBattleAndWait::CreateBattleLevelProxy(
	UGameplayAbility* OwningAbility,
	FName TaskInstanceName,
	const UPRBattleDataAsset* Data,
	const AActor* PlayerActor
)
{
	UPRAT_CreateBattleAndWait* Task = NewAbilityTask<UPRAT_CreateBattleAndWait>(OwningAbility, TaskInstanceName);

	Task->BattleLevelName = Data->BattleLevelName;
	Task->PlayerActor = PlayerActor;
	Task->BattleData = Data;

	return Task;
}

void UPRAT_CreateBattleAndWait::SetPlayerOnBattleLevel()
{
	if (!PlayerActor.IsValid())
	{
		return;
	}

	AActor* Actor = const_cast<AActor*>(PlayerActor.Get());
	if (APRCharacterBase* Char = Cast<APRCharacterBase>(Actor))
	{
		Char->SetActorLocation(Char->GetActorLocation() + FVector(-400,0 ,0));
		Char->SetLastVelocityByVector(FVector(1,0,0));
	}
}

void UPRAT_CreateBattleAndWait::Activate()
{
	if (!Ability)
	{
		EndTask();
		return;
	}

	UWorld* World = GetWorld();
	if (!World || !PlayerActor.IsValid())
	{
		EndTask();
		return;
	}

	// 기존 위치 정보 저장
	SavedLocation = PlayerActor->GetActorLocation();
	SavedRotation = PlayerActor->GetActorRotation();

	// 레벨 생성
	bool bSuccess = false;
	ULevelStreamingDynamic* Stream = ULevelStreamingDynamic::LoadLevelInstance(
		GetWorld(),
		BattleLevelName.ToString(),
		SavedLocation,
		SavedRotation,
		bSuccess
	);

	StreamRef = Stream;

	if (!bSuccess)
	{
		return;
	}

	Stream->SetShouldBeLoaded(true);
	Stream->SetShouldBeVisible(true);

	Stream->OnLevelLoaded.AddDynamic(this, &UPRAT_CreateBattleAndWait::OnLevelLoaded);
	Stream->OnLevelUnloaded.AddDynamic(this, &UPRAT_CreateBattleAndWait::OnLevelUnLoaded);
}

void UPRAT_CreateBattleAndWait::OnDestroy(bool bInOwnerFinished)
{
	// 캔슬 태그 호출 시 레벨 종료
	if (StreamRef)
	{
		StreamRef->SetShouldBeVisible(false);
		StreamRef->SetShouldBeLoaded(false);

		ULevelStreaming* Field = UGameplayStatics::GetStreamingLevel(GetWorld(), FName(TEXT("/Game/PRProject/Level/TestLevel")));
		if (Field)
		{
			Field->SetShouldBeVisible(true);
		}
	}

	// 카메라 복귀
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	APawn* Pawn = PC ? PC->GetPawn() : nullptr;
	if (PC && Pawn)
	{
		PC->SetViewTargetWithBlend(
			Pawn,
			1.0f,
			EViewTargetBlendFunction::VTBlend_EaseInOut,
			0.2f,
			true
		);
	}

	// 플레이어 위치 복귀
	AActor* Actor = const_cast<AActor*>(PlayerActor.Get());
	if (APRCharacterBase* Char = Cast<APRCharacterBase>(Actor))
	{
		Char->SetActorLocation(SavedLocation);
	}

	if (!bInOwnerFinished && ShouldBroadcastAbilityTaskDelegates())
		OnInterrupted.Broadcast();

	if (ShouldBroadcastAbilityTaskDelegates())
		OnCompleted.Broadcast();

	Super::OnDestroy(bInOwnerFinished);
}


void UPRAT_CreateBattleAndWait::OnLevelLoaded()
{
	// 레벨 생성 후 호출 함수
	ULevelStreaming* Field = UGameplayStatics::GetStreamingLevel(GetWorld(), FName(TEXT("/Game/PRProject/Level/TestLevel")));
	if (Field)
	{
		Field->SetShouldBeVisible(false);
	}

	// 임시로 캐릭터 위치 설정
	SetPlayerOnBattleLevel();

	// Enemy 스폰
	FActorSpawnParameters Params;
	Params.OverrideLevel = StreamRef->GetLoadedLevel();
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (const FEnemyInfo& Info : BattleData->EnemyInfo)
	{
		if (!Info.EnemyClass) continue;

		APaperZDCharacter* Enemy = StreamRef->GetWorld()->SpawnActor<APaperZDCharacter>(
			Info.EnemyClass,
			Info.SpawnLocation,
			Info.SpawnRotation,
			Params);
	}

	// 카메라 전환
	AActor* Manager = nullptr;
	if (ULevel* LV = StreamRef ? StreamRef->GetLoadedLevel() : nullptr)
	{
		for (AActor* A : LV->Actors)
		{
			if (IsValid(A) && A->ActorHasTag(FName("Camera")))
			{
				Manager = A;
				break;
			}
		}
	}

	if (Manager)
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
		if (PC)
		{
			PC->SetViewTargetWithBlend(
				Manager,
				2.0f,
				EViewTargetBlendFunction::VTBlend_Cubic,
				0.0f,
				true
			);
		}
		
		// 배틀 시작
		APRBattleLevelManager* BattleManager = Cast<APRBattleLevelManager>(Manager);
		if (BattleManager)
		{
			FTimerHandle InitHandle;
			GetWorld()->GetTimerManager().SetTimer(
				InitHandle,
				BattleManager,                              
				&APRBattleLevelManager::InitBattle,          
				2.0f,                                     
				false                        
			);
		}
		
	}

	// 레벨 호출 후 외부 로직 바인딩
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnLoaded.Broadcast();
	}
}

void UPRAT_CreateBattleAndWait::OnLevelUnLoaded()
{
	// 레벨 제거 이 후 처리
}
