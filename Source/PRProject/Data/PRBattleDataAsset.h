// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PRBattleDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FEnemyInfo
{
	GENERATED_BODY()

	// 스폰할 객체 정보
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class APaperZDCharacter> EnemyClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector SpawnLocation = FVector::ZeroVector;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator SpawnRotation = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level = 0;
};


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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 EnemyNumber = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FEnemyInfo> EnemyInfo;
};
