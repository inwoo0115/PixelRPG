#pragma once

#include "CoreMinimal.h"
#include "PRPlayerInputType.generated.h"

UENUM(BlueprintType)
enum class EInputType : uint8
{
	None = 0,
	BasicAttack,
	SpecialAttack,
	Dash
};