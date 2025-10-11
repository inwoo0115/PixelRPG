// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/PRGA_StartTurn.h"
#include "PRGA_StartTurn.h"
#include "Blueprint/UserWidget.h"
#include "UI/PRBattleCommandWidget.h"

UPRGA_StartTurn::UPRGA_StartTurn()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UPRGA_StartTurn::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	// UI 제거
	HideUI(ActorInfo);

	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UPRGA_StartTurn::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// UI 표시
	UE_LOG(LogTemp, Warning, TEXT("Start Turn Ability"));

	ShowUI(ActorInfo);
}

void UPRGA_StartTurn::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	// UI 제거
	HideUI(ActorInfo);

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UPRGA_StartTurn::ShowUI(const FGameplayAbilityActorInfo* ActorInfo)
{
	if (!CommandWidgetClass)
	{
		return;
	}

	APlayerController* PC = ActorInfo->PlayerController.Get();
	if (!PC)
	{
		return;
	}

	if (CommandWidget)
	{
		CommandWidget->SetVisibility(ESlateVisibility::Visible);
		CommandWidget->SetIsEnabled(true);
	}
	else
	{
		CommandWidget = CreateWidget<UUserWidget>(PC, CommandWidgetClass);
		if (!CommandWidget)
		{
			return;
		}
		CommandWidget->AddToViewport(100);
		CommandWidget->SetVisibility(ESlateVisibility::Visible);
		CommandWidget->SetIsEnabled(true);

		// Actor 기반으로 위젯 정보 초기화
		UPRBattleCommandWidget* CastWidget = Cast<UPRBattleCommandWidget>(CommandWidget);
		if (CastWidget)
		{
			CastWidget->InitWidgetInfo(ActorInfo->AvatarActor.Get());
		}
	}
}

void UPRGA_StartTurn::HideUI(const FGameplayAbilityActorInfo* ActorInfo)
{
	if (CommandWidget)
	{
		CommandWidget->RemoveFromParent();
		CommandWidget = nullptr;
	}
}
