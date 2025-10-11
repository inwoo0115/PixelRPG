// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PRAttackSkillSlotWidget.h"
#include "Components/TextBlock.h"

void UPRAttackSkillSlotWidget::SetSkillText(FText InText)
{
	SkillText->SetText(InText);
}
