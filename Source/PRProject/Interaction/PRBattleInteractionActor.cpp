// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/PRBattleInteractionActor.h"
#include "Battle/PRBattleManager.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Data/PRBattleDataAsset.h"

void APRBattleInteractionActor::Interact(AActor* InteractActor)
{
	Super::Interact(InteractActor);

	APRBattleManager* BM = APRBattleManager::Get(GetWorld());
	if (!BM)
	{
		return;
	}

	FGameplayEventData Data;
	Data.EventTag = CreateBattleTag;
	Data.Instigator = InteractActor;
	Data.Target = BM;
	Data.OptionalObject = BattleData;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(BM, CreateBattleTag, Data);;
}