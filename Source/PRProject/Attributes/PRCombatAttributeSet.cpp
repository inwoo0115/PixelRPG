// Fill out your copyright notice in the Description page of Project Settings.


#include "Attributes/PRCombatAttributeSet.h"

UPRCombatAttributeSet::UPRCombatAttributeSet() :
	Health(100.0f),
	MaxHealth(100.0f),
	Damage(10.0f),
	MaxDamage(100.0f),
	Speed(10.0f),
	MaxSpeed(100.0f)
{
}

bool UPRCombatAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{

	return Super::PreGameplayEffectExecute(Data);
}

void UPRCombatAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}

void UPRCombatAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
}

void UPRCombatAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
}

void UPRCombatAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	// Attribute Change Log
}
