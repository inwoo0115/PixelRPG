// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayTagContainer.h"
#include "PRGA_SkillAbilityBase.generated.h"

/**
 * 
 */
UCLASS()
class PRPROJECT_API UPRGA_SkillAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()

public:
	FGameplayTag GetEventTag() const;

	FText GetSkillName() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SkillName")
	FText SkillName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tag")
	FGameplayTag EventTag;
};
