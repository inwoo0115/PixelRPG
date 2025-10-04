#pragma once

#include "CoreMinimal.h"
#include "PRBattleRequest.generated.h"

// 어빌리티 송신 구조체
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
