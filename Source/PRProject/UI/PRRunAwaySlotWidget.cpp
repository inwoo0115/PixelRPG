// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PRRunAwaySlotWidget.h"
#include "AbilitySystemBlueprintLibrary.h"

void UPRRunAwaySlotWidget::ActiveCommandAction()
{
    FGameplayEventData Data;
    Data.EventTag = ActionTag;
    Data.Instigator = FollowActor.Get();
    Data.Target = FollowActor.Get();

    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(FollowActor.Get(), ActionTag, Data);
}
