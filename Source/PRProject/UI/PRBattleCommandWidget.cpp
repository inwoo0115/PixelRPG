// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PRBattleCommandWidget.h"
#include "PRBattleCommandWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CanvasPanelSlot.h"
#include "PRBattleCommandSlotWidget.h"

void UPRBattleCommandWidget::InitWidgetInfo(AActor* InActor)
{
	FollowActor = InActor;

	if (RunAwaySlot)
	{
		RunAwaySlot->SetFollowActor(FollowActor.Get());
	}
	if (AttackSlot)
	{
		AttackSlot->SetFollowActor(FollowActor.Get());
	}
	if (InventorySlot)
	{
		InventorySlot->SetFollowActor(FollowActor.Get());
	}

	// TODO 액터 정보 기반 위젯 정보 설정
}

void UPRBattleCommandWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetIsFocusable(true);
	SetKeyboardFocus();

	BuildEntryList();
	SelectedIndex = 0;
	UpdateSelectionVisuals();
}

void UPRBattleCommandWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (!PC)
	{
		return;
	}

	if (!FollowActor.IsValid())
	{
		return;
	}

	FVector2D ScreenPos;
	const bool bProjected = PC->ProjectWorldLocationToScreen(FollowActor->GetActorLocation() + FVector(0, 0, 100.f), ScreenPos, /*bPlayerViewportRelative=*/true);

	if (bProjected)
	{
		SetAnchorsInViewport(FAnchors(0, 0, 0, 0));
		SetAlignmentInViewport(FVector2D(0.f, 0.f));
		SetPositionInViewport(ScreenPos, /*bRemoveDPIScale=*/true);
		SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else
	{
		SetVisibility(ESlateVisibility::Collapsed);
	}
}

FReply UPRBattleCommandWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	const FKey Key = InKeyEvent.GetKey();

	if (Key == EKeys::W || Key == EKeys::Up)
	{
		MoveSelection(1);
		return FReply::Handled();
	}
	if (Key == EKeys::S || Key == EKeys::Down)
	{
		MoveSelection(-1);
		return FReply::Handled();
	}
	if (Key == EKeys::Enter || Key == EKeys::Virtual_Accept)
	{
		ConfirmSlotSelection();
		return FReply::Handled();
	}
	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void UPRBattleCommandWidget::BuildEntryList()
{
	Slots.Reset();
	if (RunAwaySlot)
	{
		RunAwaySlot->SetFollowActor(FollowActor.Get());
		Slots.Add(RunAwaySlot);
	}
	if (AttackSlot)
	{
		AttackSlot->SetFollowActor(FollowActor.Get());
		Slots.Add(AttackSlot);
	}
	if (InventorySlot)
	{
		InventorySlot->SetFollowActor(FollowActor.Get());
		Slots.Add(InventorySlot);
	}
}

void UPRBattleCommandWidget::UpdateSelectionVisuals()
{
	for (int32 i = 0; i < Slots.Num(); ++i)
	{
		if (auto* SelectedSlot = Slots[i].Get())
		{
			SelectedSlot->SetWidgetSelected(i == SelectedIndex);
		}
	}
}

void UPRBattleCommandWidget::MoveSelection(int32 Delta)
{
	if (Slots.Num() == 0)
	{
		return;
	}

	SelectedIndex = (SelectedIndex + Delta) % Slots.Num();

	if (SelectedIndex < 0)
	{
		SelectedIndex += Slots.Num();
	}

	UpdateSelectionVisuals();
}

void UPRBattleCommandWidget::ConfirmSlotSelection()
{
	if (Slots.IsValidIndex(SelectedIndex))
	{
		if (auto* SelectedSlot = Slots[SelectedIndex].Get())
		{
			SelectedSlot->ActiveCommandAction();
		}
	}
}
