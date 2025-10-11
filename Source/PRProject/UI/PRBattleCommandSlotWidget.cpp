// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PRBattleCommandSlotWidget.h"
#include "PRBattleCommandSlotWidget.h"
#include "Components/Border.h"

void UPRBattleCommandSlotWidget::SetWidgetSelected(bool bInSelected)
{
    bSelected = bInSelected;

    // 색깔 설정
    if (RootBorder)
    {
        RootBorder->SetBrushColor(bSelected ? SelectedColor : NormalColor);
    }
}

void UPRBattleCommandSlotWidget::SetFollowActor(AActor* InActor)
{
    FollowActor = InActor;
}

void UPRBattleCommandSlotWidget::ActiveCommandAction()
{
    // 기능 구현
}

void UPRBattleCommandSlotWidget::NativeConstruct()
{
    Super::NativeConstruct();
    SetWidgetSelected(false);
    SetIsFocusable(false);
}
