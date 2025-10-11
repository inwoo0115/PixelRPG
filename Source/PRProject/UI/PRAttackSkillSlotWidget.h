// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/PRBattleCommandSlotWidget.h"
#include "PRAttackSkillSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class PRPROJECT_API UPRAttackSkillSlotWidget : public UPRBattleCommandSlotWidget
{
	GENERATED_BODY()

public:

	int32 SlotIndex = 0;

	void SetSkillText(FText InText);

protected:
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UTextBlock> SkillText;

};
