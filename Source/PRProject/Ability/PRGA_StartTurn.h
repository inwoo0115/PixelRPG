// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "PRGA_StartTurn.generated.h"

/**
 * 
 */
UCLASS()
class PRPROJECT_API UPRGA_StartTurn : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UPRGA_StartTurn();

	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	void ShowUI(const FGameplayAbilityActorInfo* ActorInfo);

	void HideUI(const FGameplayAbilityActorInfo* ActorInfo);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UUserWidget> CommandWidgetClass;

	UPROPERTY(Transient)
	TObjectPtr<class UUserWidget> CommandWidget;
};
