#pragma once

#include "Engine/DataTable.h"
#include "PRBattleData.generated.h"

USTRUCT()
struct FBattleData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FName BattleLevelName;
};