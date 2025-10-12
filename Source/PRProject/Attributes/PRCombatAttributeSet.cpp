// Fill out your copyright notice in the Description page of Project Settings.


#include "Attributes/PRCombatAttributeSet.h"
#include "GameplayEffectExtension.h"

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

	float MinimumHealth = 0.0f;

	const float OldHealth = GetHealth();
	const float OldDamage = GetDamage();
	const float MaxHP = GetMaxHealth();

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{

		SetHealth(FMath::Clamp(GetHealth(), MinimumHealth, GetMaxHealth()));
	}
	else if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{


		SetHealth(FMath::Clamp(GetHealth() - GetDamage(), MinimumHealth, GetMaxHealth()));
		SetDamage(0.0f);

		UE_LOG(LogTemp, Warning, TEXT("[POST Damage] HP %.1f -> %.1f (¥Ä=%.1f), Damage=%.1f, Max=%.1f"),
			OldHealth, GetHealth(), GetHealth() - OldHealth, OldDamage, MaxHP);
	}
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

	if (Attribute == GetDamageAttribute())
	{
		NewValue = NewValue < 0.0f ? 0.0f : NewValue;
	}
}

void UPRCombatAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	// Attribute Change Log
}
