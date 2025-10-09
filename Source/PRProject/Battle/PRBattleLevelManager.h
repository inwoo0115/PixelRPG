// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PRBattleLevelManager.generated.h"

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

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	void InitBattle();

	void GatherAliveParticipant();

	void BuildTurnOrder();

	// Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> SpringArm;

	// Turn Battle Parameter
	int32 CurrentIndex = 0;

	UPROPERTY()
	TArray<FParticipantState> Participants;
};
