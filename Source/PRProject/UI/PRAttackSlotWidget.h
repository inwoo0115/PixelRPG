// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/PRBattleCommandSlotWidget.h"
#include "PRAttackSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class PRPROJECT_API UPRAttackSlotWidget : public UPRBattleCommandSlotWidget
{
	GENERATED_BODY()

public:
    virtual void NativeConstruct() override;
    virtual FReply NativeOnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;
    virtual void ActiveCommandAction() override;

protected:
    // ½ºÅ³ ½½·Ô Ä­
    UPROPERTY(meta = (BindWidgetOptional))
    TObjectPtr<class UVerticalBox> SkillsBox;

    // ½ºÅ³ Å¸°Ù ¼±ÅÃ
    bool bSelectingTarget = false;

    // ½ºÅ³ Å¸°Ù
    TArray<TWeakObjectPtr<AActor>> Targets;
    int32 TargetIndex = 0;

    // ½ºÅ³ ½½·Ô Å¬·¡½º
    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<UPRBattleCommandSlotWidget> SkillSlotClass;

    // ½ºÅ³ ¼±ÅÃ
    TArray<TWeakObjectPtr<UPRBattleCommandSlotWidget>> SkillSlots;
    int32 SkillIndex = 0;


    void BuildSkillListFromASC();
    void UpdateSkillSelectionVisuals();
    void MoveSkillSelection(int32 Delta);

    void EnterTargetSelectMode();
    void BuildTargetCandidates();
    void UpdateTargetHighlight();
    void MoveTargetSelection(int32 Delta);
    void ConfirmCurrent();
    void CancelOneLevel();
    void SendCastEventToSelfWithTarget();
};
