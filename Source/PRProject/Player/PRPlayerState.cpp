// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PRPlayerState.h"
#include "AbilitySystemComponent.h"
#include "Attributes/PRCombatAttributeSet.h"

APRPlayerState::APRPlayerState()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));

	// Attribute
	CombatAttribute = CreateDefaultSubobject<UPRCombatAttributeSet>(TEXT("CombatAttribute"));
}

UAbilitySystemComponent* APRPlayerState::GetAbilitySystemComponent() const
{
    return ASC;
}
