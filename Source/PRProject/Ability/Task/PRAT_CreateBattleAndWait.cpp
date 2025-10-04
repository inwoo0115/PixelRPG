// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Task/PRAT_CreateBattleAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LevelStreamingDynamic.h"
#include "Engine/StreamableManager.h"
#include "Engine/LevelStreamingDynamic.h"

UPRAT_CreateBattleAndWait* UPRAT_CreateBattleAndWait::CreateBattleLevelProxy(
	UGameplayAbility* OwningAbility,
	FName TaskInstanceName,
	FName BattleLevelName,
	const AActor* PlayerActor
)
{
	UPRAT_CreateBattleAndWait* Task = NewAbilityTask<UPRAT_CreateBattleAndWait>(OwningAbility, TaskInstanceName);

	Task->BattleLevelName = BattleLevelName;
	Task->PlayerActor = PlayerActor;

	return Task;
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
		FVector::ZeroVector,
		FRotator::ZeroRotator,
		bSuccess
	);

	if (bSuccess)
	{
		Stream->SetShouldBeLoaded(true);
		Stream->SetShouldBeVisible(true);

		Stream->OnLevelLoaded.AddDynamic(this, &UPRAT_CreateBattleAndWait::OnLevelLoaded);
		Stream->OnLevelUnloaded.AddDynamic(this, &UPRAT_CreateBattleAndWait::OnLevelUnLoaded);
	}

	StreamRef = Stream;
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
	// 몬스터 생성 및 플레이어 위치 이동


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
