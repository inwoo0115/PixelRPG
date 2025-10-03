// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "PRAT_PlaySequenceAndWait.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSequenceWaitSimpleDelegate);

/**
 * 
 */
UCLASS()
class PRPROJECT_API UPRAT_PlaySequenceAndWait : public UAbilityTask
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	FSequenceWaitSimpleDelegate	OnCompleted;

	UPROPERTY()
	FSequenceWaitSimpleDelegate	OnInterrupted;

	// ÆÑÅä¸® ÇÔ¼ö
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility"))
	static UPRAT_PlaySequenceAndWait* CreatePlaySequenceAndWaitProxy(
		UGameplayAbility* OwningAbility,
		FName TaskInstanceName, 
		class UPaperZDAnimSequence* SequenceToPlay,
		float Rate = 1.f, 
		FName SlotName = "Default",
		float StartPosition = 0.f
		);

protected:
	UPROPERTY()
	TObjectPtr<UPaperZDAnimSequence> AnimToPlay;

	UPROPERTY()
	TObjectPtr<class UPaperZDAnimInstance> AnimInstance;

	UPROPERTY()
	float Rate;

	UPROPERTY()
	FName SlotName;

	UPROPERTY()
	float StartPosition;

	UPROPERTY()
	bool bPlayValid = false;

	virtual void Activate() override;
	virtual void OnDestroy(bool bInOwnerFinished) override;

private:
	void OnAnimEnd(bool bCompleted);


};
