// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "PRAT_CreateBattleAndWait.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCreateBattleSimpleDelegate);

/**
 * 
 */
UCLASS()
class PRPROJECT_API UPRAT_CreateBattleAndWait : public UAbilityTask
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	FCreateBattleSimpleDelegate	OnCompleted;

	UPROPERTY()
	FCreateBattleSimpleDelegate	OnLoaded;

	UPROPERTY()
	FCreateBattleSimpleDelegate	OnInterrupted;

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks",
		meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility"))
	static UPRAT_CreateBattleAndWait* CreateBattleLevelProxy(
		UGameplayAbility* OwningAbility,
		FName TaskInstanceName,
		FName BattleLevelName,
		const AActor* Player
	);

protected:

	virtual void Activate() override;
	virtual void OnDestroy(bool bInOwnerFinished) override;

	// TODO: 임시로 레벨 이름만 넣음
	FName BattleLevelName;

	TWeakObjectPtr<const AActor> PlayerActor;

	FVector SavedLocation = FVector::ZeroVector;
	FRotator SavedRotation = FRotator::ZeroRotator;

	UPROPERTY()
	TObjectPtr<class ULevelStreamingDynamic> StreamRef;

	UFUNCTION() 
	void OnLevelLoaded();

	UFUNCTION()
	void OnLevelUnLoaded();
};
