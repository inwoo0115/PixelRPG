// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/PRGA_RunAway.h"
#include "PRGA_RunAway.h"
#include "Battle/PRBattleLevelManager.h"

UPRGA_RunAway::UPRGA_RunAway()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

}

void UPRGA_RunAway::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UPRGA_RunAway::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// Phase 상태값 변경
	APRBattleLevelManager* Manager = APRBattleLevelManager::Get(GetWorld());

	if (Manager)
	{
		Manager->SetBattleResult(EBattleResult::Runaway);
		Manager->OnExecuteCommand();
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

void UPRGA_RunAway::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
