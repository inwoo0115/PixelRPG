// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PRPlayerState.h"
#include "AbilitySystemComponent.h"

APRPlayerState::APRPlayerState()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
}

UAbilitySystemComponent* APRPlayerState::GetAbilitySystemComponent() const
{
    return ASC;
}
