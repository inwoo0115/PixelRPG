// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PRBattleCommandWidget.h"
#include "PRBattleCommandWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CanvasPanelSlot.h"

void UPRBattleCommandWidget::InitWidgetInfo(AActor* InActor)
{
	FollowActor = InActor;

	// TODO 액터 정보 기반 위젯 정보 설정
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
	const bool bProjected = PC->ProjectWorldLocationToScreen(FollowActor->GetActorLocation(), ScreenPos, /*bPlayerViewportRelative=*/true);

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
