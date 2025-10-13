#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"  
#include "Character/PRPlayerInputType.h"
#include "PRSkillData.generated.h"


UCLASS()
class USkillData : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray <TObjectPtr<AActor>> TargetActors;

	UPROPERTY()
	int32 InputType;

	// 기타 스킬 정보 추가
	// ...
};