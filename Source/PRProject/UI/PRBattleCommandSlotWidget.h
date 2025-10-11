// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayTagContainer.h"
#include "PRBattleCommandSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class PRPROJECT_API UPRBattleCommandSlotWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetWidgetSelected(bool bInSelected);

    void SetFollowActor(AActor* InActor);

    virtual void ActiveCommandAction();

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tag")
    FGameplayTag ActionTag;

    UPROPERTY(meta = (BindWidgetOptional))
    class UBorder* RootBorder;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visual")
    FLinearColor NormalColor = FLinearColor(1, 1, 1, 1);

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visual")
    FLinearColor SelectedColor = FLinearColor(0.3f, 0.8f, 1.f, 1);

protected:
    virtual void NativeConstruct() override;

    UPROPERTY()
    TWeakObjectPtr<AActor> FollowActor;

    bool bSelected = false;
};
