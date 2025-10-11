// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PRPlayerController.h"
#include "PRPlayerController.h"

void APRPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// ASC Debug TODO: 나중에 지우기
	ConsoleCommand(TEXT("showdebug abilitysystem"));
}

void APRPlayerController::StartBattleUIMode()
{
    FInputModeGameAndUI Mode;
    Mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
    Mode.SetHideCursorDuringCapture(true);
    SetInputMode(Mode);

    bShowMouseCursor = true;

    SetIgnoreMoveInput(true);
    SetIgnoreLookInput(true);
}

void APRPlayerController::EndBattleUIMode()
{
    FInputModeGameOnly Mode;
    SetInputMode(Mode);

    bShowMouseCursor = false;

    SetIgnoreMoveInput(false);
    SetIgnoreLookInput(false);
}
