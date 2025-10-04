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

	// ���� ��ġ ���� ����
	SavedLocation = PlayerActor->GetActorLocation();
	SavedRotation = PlayerActor->GetActorRotation();

	// ���� ����
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
	// ĵ�� �±� ȣ�� �� ���� ����
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
	// ���� ���� �� ȣ�� �Լ�
	ULevelStreaming* Field = UGameplayStatics::GetStreamingLevel(GetWorld(), FName(TEXT("/Game/PRProject/Level/TestLevel")));
	if (Field)
	{
		Field->SetShouldBeVisible(false);
	}
	// ���� ���� �� �÷��̾� ��ġ �̵�


	// ���� ȣ�� �� �ܺ� ���� ���ε�
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnLoaded.Broadcast();
	}
}

void UPRAT_CreateBattleAndWait::OnLevelUnLoaded()
{
	// ���� ���� �� �� ó��
}
