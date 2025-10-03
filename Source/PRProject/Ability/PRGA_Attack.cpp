// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/PRGA_Attack.h"
#include "PRGA_Attack.h"
#include "Tag/PRGameplayTag.h"
#include "Character/PRCharacterBase.h"
#include "Task/PRAT_PlaySequenceAndWait.h"
#include "GameFramework/CharacterMovementComponent.h"

UPRGA_Attack::UPRGA_Attack()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UPRGA_Attack::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UPRGA_Attack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	CachedCharacter = Cast<APRCharacterBase>(ActorInfo->AvatarActor.Get());
	if (!CachedCharacter)
	{
		return;
	}

	// 공격 중 움직임 제거
	CachedCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

	UPRAT_PlaySequenceAndWait* PlaySequenceTask = UPRAT_PlaySequenceAndWait::CreatePlaySequenceAndWaitProxy(
		this,
		FName(TEXT("PlayAttackSequence")),
		AttackAnim,
		Rate,
		"Default",
		StartPosition
	);

	PlaySequenceTask->OnCompleted.AddDynamic(this, &UPRGA_Attack::OnAttackMontageComplete);
	PlaySequenceTask->OnInterrupted.AddDynamic(this, &UPRGA_Attack::OnAttackMontageInterrupted);
	PlaySequenceTask->ReadyForActivation();
}

void UPRGA_Attack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	CachedCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void UPRGA_Attack::OnAttackMontageComplete()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UPRGA_Attack::OnAttackMontageInterrupted()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);

}
