// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "PRGA_ChooseAndCastSKill.generated.h"

/**
 * 
 */
UCLASS()
class PRPROJECT_API UPRGA_ChooseAndCastSKill : public UGameplayAbility
{
	GENERATED_BODY()


public:
	UPRGA_ChooseAndCastSKill();

	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
	UFUNCTION()
	void OnSkillComplete(const FAbilityEndedData& Data);

	FDelegateHandle AbilityEndedHandle;

	FGameplayAbilitySpecHandle RoutedSpecHandle;
};
