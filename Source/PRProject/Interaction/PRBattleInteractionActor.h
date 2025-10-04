// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/PRInteractionActorBase.h"
#include "GameplayTagContainer.h"
#include "PRBattleInteractionActor.generated.h"

/**
 * 
 */
UCLASS()
class PRPROJECT_API APRBattleInteractionActor : public APRInteractionActorBase
{
	GENERATED_BODY()
	
public:
	virtual void Interact(AActor* InteractActor) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DataAsset")
	TObjectPtr<class UPRBattleDataAsset> BattleData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tag")
	FGameplayTag CreateBattleTag;
};
