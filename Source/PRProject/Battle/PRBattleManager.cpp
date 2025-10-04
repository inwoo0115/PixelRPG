// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/PRBattleManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameplayAbilitySpec.h"
#include "AbilitySystemComponent.h"

APRBattleManager* APRBattleManager::Singleton = nullptr;

APRBattleManager::APRBattleManager()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
}

void APRBattleManager::BeginPlay()
{
	Super::BeginPlay();

	Singleton = this;

	if (ASC)
	{
		ASC->InitAbilityActorInfo(this, this);

		// Ability µî·Ï
		for (const auto& StartAbility : StartAbilties)
		{
			FGameplayAbilitySpec StartSpec(StartAbility);
			ASC->GiveAbility(StartSpec);
		}
	}
}

APRBattleManager* APRBattleManager::Get(UWorld* World)
{
	if (Singleton)
	{
		return Singleton;
	}

	return Cast<APRBattleManager>(UGameplayStatics::GetActorOfClass(World, APRBattleManager::StaticClass()));
}

UAbilitySystemComponent* APRBattleManager::GetAbilitySystemComponent() const
{
	return ASC;
}
