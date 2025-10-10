// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "PRBattleLevelManager.generated.h"

UENUM()
enum class EBattlePhase : uint8
{
	None, 
	Intro, 
	StartTurn, 
	AwaitCommand, 
	Execute, 
	EndTurn, 
	EndBattle
};

UENUM()
enum class EBattleResult : uint8
{
	None,
	Victory,
	Defeat,
	Runaway
};

USTRUCT()
struct FParticipantState
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TWeakObjectPtr<AActor> Actor;

	UPROPERTY()
	float Speed = 0.f;

	UPROPERTY()
	bool  bAlive = true;

	UPROPERTY()
	bool  bIsAlly = false;

	UPROPERTY()
	int32 TieRoll = 0;

	UPROPERTY()
	uint64 StableId = 0;

	static bool SortPredicate(const FParticipantState& L, const FParticipantState& R)
	{
		if (L.Speed != R.Speed) 
			return L.Speed > R.Speed;
		if (L.TieRoll != R.TieRoll) 
			return L.TieRoll > R.TieRoll;
		return L.StableId < R.StableId;
	}
};

UCLASS()
class PRPROJECT_API APRBattleLevelManager : public AActor
{
	GENERATED_BODY()
	
public:	
	APRBattleLevelManager();

	void InitBattle();

	static APRBattleLevelManager* Get(UWorld* World);

	void OnExecuteCommand();

	void SetBattleResult(EBattleResult NewResult);

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	// Init Battle System
	void GatherAliveParticipant();

	void BuildTurnOrder();

	// Phase Fucntion
	void StartPhase(EBattlePhase NewPhase);

	void PhaseIntro();

	void PhaseStartTurn();

	void PhaseAwaitCommand();

	void PhaseExecute();
	
	void PhaseEndTurn();
	
	void PhaseEndBattle();

	bool CheckBattleResult();

	// Phase Tag
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tag")
	FGameplayTag StartTurnTag;

	// Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> SpringArm;

	// Battle Parameter
	int32 CurrentIndex = 0;

	UPROPERTY()
	TArray<FParticipantState> Participants;

	// Battle Phase
	EBattlePhase CurrentPhase = EBattlePhase::None;

	EBattleResult Result = EBattleResult::None;

	// SingleTon
	static APRBattleLevelManager* Singleton;
};
