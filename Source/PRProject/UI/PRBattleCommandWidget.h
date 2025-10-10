// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayTagContainer.h"
#include "PRBattleCommandWidget.generated.h"

/**
 * 
 */
UCLASS()
class PRPROJECT_API UPRBattleCommandWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitWidgetInfo(AActor* InActor);

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY() 
	TWeakObjectPtr<AActor> FollowActor;

	// GAS Tag
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tag")
	FGameplayTag CastSkillTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tag")
	FGameplayTag RunAwayTag;
};
