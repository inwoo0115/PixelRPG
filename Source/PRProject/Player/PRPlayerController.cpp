// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PRPlayerController.h"
#include "PRPlayerController.h"

void APRPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// ASC Debug TODO: 나중에 지우기
	ConsoleCommand(TEXT("showdebug abilitysystem"));
}
