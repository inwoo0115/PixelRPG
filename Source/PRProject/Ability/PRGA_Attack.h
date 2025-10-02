// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "PRGA_Attack.generated.h"

/**
 * 
 */
UCLASS()
class PRPROJECT_API UPRGA_Attack : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UPRGA_Attack();

	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	UPROPERTY(Transient, DuplicateTransient)
	TObjectPtr<class APRCharacterBase> CachedCharacter;
};
