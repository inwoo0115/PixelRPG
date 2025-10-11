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
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	UPROPERTY() 
	TWeakObjectPtr<AActor> FollowActor;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UPRBattleCommandSlotWidget> RunAwaySlot;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UPRBattleCommandSlotWidget> InventorySlot;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UPRBattleCommandSlotWidget> AttackSlot;

	int32 SelectedIndex = 0;

	UPROPERTY()
	TArray<TWeakObjectPtr<UPRBattleCommandSlotWidget>> Slots;

	// GAS Tag
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tag")
	FGameplayTag CastSkillTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tag")
	FGameplayTag RunAwayTag;

	// Slot Function
	void BuildEntryList();
	void UpdateSelectionVisuals();
	void MoveSelection(int32 Delta);
	void ConfirmSlotSelection();
};
