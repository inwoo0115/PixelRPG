// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTrigger/PRRandomEncounterTrigger.h"
#include "Character/PRPlayerCharacter.h"
#include "Battle/PRBattleRequest.h"
#include "Battle/PRBattleManager.h"

APRRandomEncounterTrigger::APRRandomEncounterTrigger()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APRRandomEncounterTrigger::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &APRRandomEncounterTrigger::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &APRRandomEncounterTrigger::OnOverlapEnd);
}

void APRRandomEncounterTrigger::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (TrackedActor.IsValid())
	{
		const FVector Cur = TrackedActor->GetActorLocation();
		const float Delta = FVector::Dist2D(Cur, LastPos);
		LastPos = Cur;

		if (Delta > KINDA_SMALL_NUMBER && StepPerIncrease > 0.f)
		{
			AccumulatedDist += Delta;

			while (AccumulatedDist >= StepPerIncrease)
			{
				AccumulatedDist -= StepPerIncrease;
				CurrentChance += ChancePerStepIncrease;
				CurrentChance = FMath::Clamp(CurrentChance, 0.f, MaxEncounterChance);
			}
		}
	}
}

void APRRandomEncounterTrigger::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (Cast<APRPlayerCharacter>(OtherActor))
	{
		TrackedActor = OtherActor;
		LastPos = OtherActor->GetActorLocation();

		if (UWorld* W = GetWorld())
		{
			if (!CheckTimer.IsValid() && CheckIntervalSeconds > 0.f)
			{
				W->GetTimerManager().SetTimer(
					CheckTimer, this, &APRRandomEncounterTrigger::CheckEncounter,
					CheckIntervalSeconds, true
				);
			}
		}
	}
}

void APRRandomEncounterTrigger::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor == TrackedActor.Get())
	{
		ResetChance();

		if (UWorld* W = GetWorld())
		{
			W->GetTimerManager().ClearTimer(CheckTimer);
		}

		TrackedActor = nullptr;
	}
}

void APRRandomEncounterTrigger::CheckEncounter()
{
	if (!TrackedActor.IsValid()) return;

	// 누적 확률로 판정
	const float Roll = FMath::FRandRange(0.f, 100.f);
	if (Roll <= CurrentChance)
	{
		SendBattleRequest();

		// 확률 리셋
		ResetChance();
	}
}

void APRRandomEncounterTrigger::SendBattleRequest()
{
	if (APRBattleManager* BM = APRBattleManager::Get(GetWorld()))
	{
		// Ability tag로 송신
	}
}

void APRRandomEncounterTrigger::ResetChance()
{
	AccumulatedDist = 0.f;
	CurrentChance = 0.f;
}
