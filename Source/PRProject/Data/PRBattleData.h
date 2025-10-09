#pragma once

#include "Engine/DataTable.h"
#include "PRBattleData.generated.h"

USTRUCT()
struct FBattleData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FName BattleLevelName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 EnemyNumber;

	// 배열 순서대로 배치됨
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<class APaperZDCharacter>> Enemy;

};