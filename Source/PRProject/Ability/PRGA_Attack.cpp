// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/PRGA_Attack.h"
#include "PRGA_Attack.h"
#include "Tag/PRGameplayTag.h"
#include "Character/PRCharacterBase.h"

UPRGA_Attack::UPRGA_Attack()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UPRGA_Attack::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

}

void UPRGA_Attack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	CachedCharacter = Cast<APRCharacterBase>(ActorInfo->AvatarActor.Get());
	if (CachedCharacter)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Test"));
	}
}
