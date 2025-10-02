// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PRAnimationDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class PRPROJECT_API UPRAnimationDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TObjectPtr<class UPaperZDAnimSequence> IdleAnim;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TObjectPtr<class UPaperZDAnimSequence> RunAnim;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TObjectPtr<class UPaperZDAnimSequence> AttackAnim;
};
