// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/PRGA_CreateAssignBattle.h"
#include "Tag/PRGameplayTag.h"
#include "Task/PRAT_CreateBattleAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayTag.h"
#include "Data/PRBattleDataAsset.h"

UPRGA_CreateAssignBattle::UPRGA_CreateAssignBattle()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UPRGA_CreateAssignBattle::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UPRGA_CreateAssignBattle::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	const UPRBattleDataAsset* Data = Cast<UPRBattleDataAsset>(TriggerEventData->OptionalObject);
	
	if (!Data)
	{
		// 어빌리티 종료
		Super::EndAbility(Handle, ActorInfo, ActivationInfo, false, true);
	}

	// Task 생성
	UPRAT_CreateBattleAndWait* CreateBattleTask = UPRAT_CreateBattleAndWait::CreateBattleLevelProxy(
		this,
		FName(TEXT("CreateBattleTask")),
		Data->BattleLevelName,
		TriggerEventData->Instigator
	);

	CreateBattleTask->OnCompleted.AddDynamic(this, &UPRGA_CreateAssignBattle::OnBattleComplete);
	CreateBattleTask->OnInterrupted.AddDynamic(this, &UPRGA_CreateAssignBattle::OnBattleInterrupted);
	CreateBattleTask->ReadyForActivation();
}

void UPRGA_CreateAssignBattle::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	// 승패 여부에 따른 결과 처리
}

void UPRGA_CreateAssignBattle::OnBattleComplete()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UPRGA_CreateAssignBattle::OnBattleInterrupted()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
