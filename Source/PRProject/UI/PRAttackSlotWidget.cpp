// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PRAttackSlotWidget.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "Ability/SkillAbility/PRGA_SkillAbilityBase.h"

#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"

#include "Character/PRCharacterBase.h"
#include "PRAttackSkillSlotWidget.h"

#include "Battle/PRBattleLevelManager.h"
#include "Data/PRSkillData.h"

void UPRAttackSlotWidget::NativeConstruct()
{
    Super::NativeConstruct();

    SetIsFocusable(false);
    SkillSlots.Reset();
    SkillIndex = 0;
    bSelectingTarget = false;
    Targets.Reset();
    TargetIndex = 0;

    UpdateSkillSelectionVisuals();
}

FReply UPRAttackSlotWidget::NativeOnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
    const FKey Key = InKeyEvent.GetKey();

    if (!bSelectingTarget)
    {
        // 스킬 선택 모드
        if (Key == EKeys::W || Key == EKeys::Up) { MoveSkillSelection(-1); return FReply::Handled(); }
        if (Key == EKeys::S || Key == EKeys::Down) { MoveSkillSelection(+1); return FReply::Handled(); }
        if (Key == EKeys::Enter || Key == EKeys::Virtual_Accept) { ConfirmCurrent(); return FReply::Handled(); }
        if (Key == EKeys::Escape || Key == EKeys::BackSpace) { CancelOneLevel(); return FReply::Handled(); }
    }
    else
    {
        // 타겟 선택 모드
        if (Key == EKeys::W || Key == EKeys::Up) { MoveTargetSelection(-1); return FReply::Handled(); }
        if (Key == EKeys::S || Key == EKeys::Down) { MoveTargetSelection(+1); return FReply::Handled(); }
        if (Key == EKeys::Enter || Key == EKeys::Virtual_Accept) { ConfirmCurrent(); return FReply::Handled(); }
        if (Key == EKeys::Escape || Key == EKeys::BackSpace) { CancelOneLevel(); return FReply::Handled(); }
    }

    return Super::NativeOnKeyDown(MyGeometry, InKeyEvent);
}

void UPRAttackSlotWidget::ActiveCommandAction()
{
    // 스킬 선택 상태 활성화
    SetIsFocusable(true);
    SetKeyboardFocus();

    BuildSkillListFromASC();
    bSelectingTarget = false;
    UpdateSkillSelectionVisuals();
}

void UPRAttackSlotWidget::BuildSkillListFromASC()
{
    if (!SkillsBox)
    {
        return;
    }

    // 스킬 슬롯 초기화
    SkillsBox->ClearChildren();
    SkillSlots.Reset();

    AActor* Owner = FollowActor.Get();
    if (!Owner)
    {
        return;
    }

    UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Owner);
    if (!ASC)
    {
        return;
    }

    // 스킬 어빌리티 불러오기
    APRCharacterBase* Char = Cast<APRCharacterBase>(Owner);
    if (!Char)
    {
        return;
    }

    int32 SlotIdx = 0;

    for (const auto& AbilityClass : Char->GetSkillAbilities())
    {
        if (!*AbilityClass.Value)
        {
            continue;
        }

        const UGameplayAbility* CDO = AbilityClass.Value->GetDefaultObject<UGameplayAbility>();
        if (!CDO)
        {
            continue;
        }

        // 엔트리 위젯 생성
        UPRAttackSkillSlotWidget* SkillSlot = CreateWidget<UPRAttackSkillSlotWidget>(GetOwningPlayer(), SkillSlotClass);
        if (!SkillSlot)
        {
            continue;
        }

        const UPRGA_SkillAbilityBase* SkillInfo = Cast<UPRGA_SkillAbilityBase>(CDO);

        SkillSlot->SetSkillText(SkillInfo->GetSkillName());

        SkillSlot->ActionTag = ActionTag;
        SkillSlot->SlotIndex = (int32)AbilityClass.Key;

        // VerticalBox에 추가
        if (UVerticalBoxSlot* BoxSlot = SkillsBox->AddChildToVerticalBox(SkillSlot))
        {
            BoxSlot->SetPadding(FMargin(0, 4));
        }

        SkillSlots.Add(SkillSlot);
    }


    // 처음 항목 하이라이트
    SkillIndex = 0;
    UpdateSkillSelectionVisuals();
}

void UPRAttackSlotWidget::UpdateSkillSelectionVisuals()
{
    for (int32 i = 0; i < SkillSlots.Num(); ++i)
    {
        if (auto* E = SkillSlots[i].Get())
        {
            E->SetWidgetSelected(i == SkillIndex);
        }
    }
}

void UPRAttackSlotWidget::MoveSkillSelection(int32 Delta)
{
    if (SkillSlots.Num() == 0)
    {
        return;
    }

    SkillIndex = (SkillIndex + Delta) % SkillSlots.Num();
    if (SkillIndex < 0)
    {
        SkillIndex += SkillSlots.Num();
    }

    UpdateSkillSelectionVisuals();
}

void UPRAttackSlotWidget::EnterTargetSelectMode()
{
    bSelectingTarget = true;
    BuildTargetCandidates();
    UpdateTargetHighlight();
}

void UPRAttackSlotWidget::BuildTargetCandidates()
{
    Targets.Reset();
    TargetIndex = 0;

    UWorld* World = GetWorld();
    if (!World) return;

    // Enemy 배열에 추가
    if (APRBattleLevelManager* Mgr = APRBattleLevelManager::Get(GetWorld()))
    {
        TArray<TWeakObjectPtr<AActor>> Enemies = Mgr->GetAliveEnemies();
        Targets = MoveTemp(Enemies);
    }
}

void UPRAttackSlotWidget::UpdateTargetHighlight()
{
    // 임시로 디버그 스피어로 표시
    if (!bSelectingTarget || Targets.Num() == 0) return;

    for (int32 i = 0; i < Targets.Num(); ++i)
    {
        if (AActor* T = Targets[i].Get())
        {
            const float Radius = (i == TargetIndex) ? 42.f : 24.f;
            DrawDebugSphere(GetWorld(), T->GetActorLocation() + FVector(0, 0, 80), Radius, 16, (i == TargetIndex) ? FColor::Cyan : FColor::White, false, 0.1f);
        }
    }
}

void UPRAttackSlotWidget::MoveTargetSelection(int32 Delta)
{
    if (Targets.Num() == 0) return;
    TargetIndex = (TargetIndex + Delta) % Targets.Num();
    if (TargetIndex < 0) TargetIndex += Targets.Num();
    UpdateTargetHighlight();
}

void UPRAttackSlotWidget::ConfirmCurrent()
{
    if (!bSelectingTarget)
    {
        // 타겟 선택 모드
        if (!SkillSlots.IsValidIndex(SkillIndex))
        {
            return;
        }
        EnterTargetSelectMode();
    }
    else
    {
        // 이벤트 송신
        SendCastEventToSelfWithTarget();
        // 끝났으면 모드 해제(원한다면)
        bSelectingTarget = false;
        Targets.Reset();
        TargetIndex = 0;
    }
}

void UPRAttackSlotWidget::CancelOneLevel()
{
    if (bSelectingTarget)
    {
        // 스킬 선택 모드로 변경
        bSelectingTarget = false;
        Targets.Reset();
        TargetIndex = 0;
        UpdateSkillSelectionVisuals();
    }
    else
    {
        // 스킬 선택 상태에서 취소 시
        // RemoveFromParent();
    }
}

void UPRAttackSlotWidget::SendCastEventToSelfWithTarget()
{
    UE_LOG(LogTemp, Warning, TEXT("SendCastEventToSelfWithTarget"));

    // 이벤트 캐릭터에 송신
    UPRAttackSkillSlotWidget* CurrentSlot = Cast<UPRAttackSkillSlotWidget>(SkillSlots[SkillIndex]);

    USkillData* SkillData = NewObject<USkillData>();
    SkillData->InputType = CurrentSlot->SlotIndex;
    SkillData->TargetActors.Add(Targets[TargetIndex].Get());

    FGameplayEventData Data;
    Data.EventTag = ActionTag;
    Data.OptionalObject = SkillData;
    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(FollowActor.Get(), ActionTag, Data);

}
