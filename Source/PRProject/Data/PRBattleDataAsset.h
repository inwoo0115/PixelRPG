// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PRBattleDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class PRPROJECT_API UPRBattleDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName BattleLevelName;
};
