// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/SkillAbility/PRGA_SkillAbilityBase.h"
#include "Battle/PRBattleLevelManager.h"


UPRGA_SkillAbilityBase::UPRGA_SkillAbilityBase()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

}

void UPRGA_SkillAbilityBase::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

}

void UPRGA_SkillAbilityBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, /*bReplicateEnd=*/true, /*bWasCancelled=*/false);

}

void UPRGA_SkillAbilityBase::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	// Phase 상태값 변경
	APRBattleLevelManager* Manager = APRBattleLevelManager::Get(GetWorld());

	if (Manager)
	{
		Manager->OnExecuteCommand();
	}
}

FGameplayTag UPRGA_SkillAbilityBase::GetEventTag() const
{
	return EventTag;
}

FText UPRGA_SkillAbilityBase::GetSkillName() const
{
	return SkillName;
}
