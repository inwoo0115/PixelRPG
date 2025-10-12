// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Static.h"
#include "PRGC_DefaultAttackEffect.generated.h"

/**
 * 
 */
UCLASS()
class PRPROJECT_API UPRGC_DefaultAttackEffect : public UGameplayCueNotify_Static
{
	GENERATED_BODY()

public:
	UPRGC_DefaultAttackEffect();

	virtual bool OnExecute_Implementation(AActor* Target, const FGameplayCueParameters& Parameters) const override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayCue)
	TObjectPtr<class UParticleSystem> ParticleSystem;
	
};
