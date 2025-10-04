// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/PRGA_EndBattle.h"
#include "PRGA_EndBattle.h"

UPRGA_EndBattle::UPRGA_EndBattle()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UPRGA_EndBattle::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UPRGA_EndBattle::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// ���� ��� ������ �� ó��
	UE_LOG(LogTemp, Warning, TEXT("ASD"))
	// �ʿ� �� Task �߰�

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

void UPRGA_EndBattle::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
