// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "GameplayTagContainer.h"
#include "Battle/PRBattleRequest.h"
#include "PRRandomEncounterTrigger.generated.h"

/**
 * 
 */
UCLASS()
class PRPROJECT_API APRRandomEncounterTrigger : public ATriggerBox
{
	GENERATED_BODY()
	
public:
	APRRandomEncounterTrigger();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EncounterInfo")
	FBattleRequest BattleRequest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EncounterInfo")
	FGameplayTag EventTag;

	void CheckEncounter();

	void SendBattleRequest();

	void ResetChance();

	FVector LastPos = FVector::ZeroVector;
	float   AccumulatedDist = 0.f;
	float   CurrentChance = 0.f;

	UPROPERTY()
	TWeakObjectPtr<AActor> TrackedActor;

	FTimerHandle CheckTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Encounter")
	float StepPerIncrease = 300.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Encounter")
	float ChancePerStepIncrease = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Encounter")
	float CheckIntervalSeconds = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Encounter")
	float MaxEncounterChance = 30.f;
};
