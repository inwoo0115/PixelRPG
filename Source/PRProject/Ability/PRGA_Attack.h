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

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
	UFUNCTION()
	void OnAttackMontageComplete();

	UFUNCTION()
	void OnAttackMontageInterrupted();

	UPROPERTY(Transient, DuplicateTransient)
	TObjectPtr<class APRCharacterBase> CachedCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class UPaperZDAnimSequence> AttackAnim;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Rate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float StartPosition;
};
