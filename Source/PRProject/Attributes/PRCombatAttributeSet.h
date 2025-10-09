// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PRAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "PRCombatAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class PRPROJECT_API UPRCombatAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UPRCombatAttributeSet();

	ATTRIBUTE_ACCESSORS(UPRCombatAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UPRCombatAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UPRCombatAttributeSet, Damage);
	ATTRIBUTE_ACCESSORS(UPRCombatAttributeSet, MaxDamage);
	ATTRIBUTE_ACCESSORS(UPRCombatAttributeSet, Speed);
	ATTRIBUTE_ACCESSORS(UPRCombatAttributeSet, MaxSpeed);

	virtual bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	
	mutable FPRAttributeEvent OnHealthChanged;

private:
	UPROPERTY(BlueprintReadOnly, Category = "Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, Category = "Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;

	UPROPERTY(BlueprintReadOnly, Category = "Damage", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Damage;

	UPROPERTY(BlueprintReadOnly, Category = "Damage", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxDamage;

	UPROPERTY(BlueprintReadOnly, Category = "Speed", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Speed;

	UPROPERTY(BlueprintReadOnly, Category = "Speed", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxSpeed;
};
