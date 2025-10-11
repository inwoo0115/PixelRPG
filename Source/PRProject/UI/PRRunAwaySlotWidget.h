// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/PRBattleCommandSlotWidget.h"
#include "PRRunAwaySlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class PRPROJECT_API UPRRunAwaySlotWidget : public UPRBattleCommandSlotWidget
{
	GENERATED_BODY()

public:

	virtual void ActiveCommandAction() override;
	
};
