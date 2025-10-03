// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDAnimInstance.h"
#include "PRAnimInstance.generated.h"

/**
 * 
 */
UCLASS(abstract, BlueprintType, Transient, Blueprintable)
class PRPROJECT_API UPRAnimInstance : public UPaperZDAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;

	void SetAnimationData(class UPRAnimationDataAsset* NewData);

	FVector GetLastVelocity() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	FVector Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	FVector LastVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimationData")
	TObjectPtr<class UPRAnimationDataAsset> AnimData = nullptr;
};
