// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayTagContainer.h"
#include "PRGA_SkillAbilityBase.generated.h"

/**
 * 
 */
UCLASS()
class PRPROJECT_API UPRGA_SkillAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPRGA_SkillAbilityBase();

	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;


	FGameplayTag GetEventTag() const;

	FText GetSkillName() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SkillName")
	FText SkillName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tag")
	FGameplayTag EventTag;
};
