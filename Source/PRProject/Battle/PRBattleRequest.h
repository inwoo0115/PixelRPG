#pragma once

#include "CoreMinimal.h"
#include "PRBattleRequest.generated.h"

// �����Ƽ �۽� ����ü
USTRUCT(BlueprintType)
struct FBattleRequest
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) 
    FName BattleLevelName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite) 
    FName EnemyGroupRowName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float EnemyNumber;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float LevelOffset;
};
