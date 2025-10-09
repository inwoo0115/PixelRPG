// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/PRBattleLevelManager.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interface/PRBattleInterface.h"
#include "Kismet/GameplayStatics.h"

APRBattleLevelManager::APRBattleLevelManager()
{
	PrimaryActorTick.bCanEverTick = true;

	// Camera, Spring Arm 설정
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

}

void APRBattleLevelManager::BeginPlay()
{
	Super::BeginPlay();
	
	//InitBattle();
}

void APRBattleLevelManager::InitBattle()
{
	GatherAliveParticipant();
	BuildTurnOrder();
}

void APRBattleLevelManager::GatherAliveParticipant()
{
	Participants.Empty();

	uint64 Index = 0;

	// Level에 있는 액터 수집
	TArray<AActor*> Cands;
	UGameplayStatics::GetAllActorsWithInterface(this, UPRBattleInterface::StaticClass(), Cands);

    for (AActor* A : Cands)
    {
        if (!IsValid(A)) continue;

        FParticipantState S;
        S.Actor = A;
        S.Speed = IPRBattleInterface::Execute_GetSpeed(A);
        S.bAlive = IPRBattleInterface::Execute_IsAlive(A);
		S.StableId = Index;

		Index++;
        Participants.Add(S);
    }
}

void APRBattleLevelManager::BuildTurnOrder()
{
	Participants.RemoveAll([](const FParticipantState& S) { return !S.Actor.IsValid() || !S.bAlive; });

	for (FParticipantState& S : Participants)
	{
		S.TieRoll = FMath::Rand();
	}

	Participants.Sort(FParticipantState::SortPredicate);
}

void APRBattleLevelManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

