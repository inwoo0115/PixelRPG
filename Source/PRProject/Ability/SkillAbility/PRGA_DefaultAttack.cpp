// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/SkillAbility/PRGA_DefaultAttack.h"
#include "PRGA_DefaultAttack.h"
#include "Data/PRSkillData.h"
#include "Ability/Task/PRAT_PlaySequenceAndWait.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"


UPRGA_DefaultAttack::UPRGA_DefaultAttack()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

}

void UPRGA_DefaultAttack::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

}

void UPRGA_DefaultAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);


	UE_LOG(LogTemp, Warning, TEXT("Cast Default Attack"));

	if (!TriggerEventData || !TriggerEventData->OptionalObject)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, /*bReplicateEnd=*/true, /*bWasCancelled=*/false);
		return;
	}

	const USkillData* SkillData = Cast<USkillData>(TriggerEventData->OptionalObject);

	CurrentTargets.Reset();

	if (SkillData)
	{
		for (AActor* T : SkillData->TargetActors)
		{
			if (IsValid(T)) CurrentTargets.Add(T);
		}
	}

	if (SkillAnim)
	{
		// 스킬 애니메이션 재생
		UPRAT_PlaySequenceAndWait* PlaySequenceTask = UPRAT_PlaySequenceAndWait::CreatePlaySequenceAndWaitProxy(
			this,
			FName(TEXT("PlaySkillSequence")),
			SkillAnim,
			Rate,
			"Default",
			StartPosition
		);

		PlaySequenceTask->OnCompleted.AddDynamic(this, &UPRGA_DefaultAttack::OnSkillMontageComplete);
		PlaySequenceTask->OnInterrupted.AddDynamic(this, &UPRGA_DefaultAttack::OnSkillMontageInterrupted);
		PlaySequenceTask->ReadyForActivation();
	}

	// 데미지 적용
	UAbilitySystemComponent* SourceASC = GetAbilitySystemComponentFromActorInfo();

	for (auto Target : CurrentTargets)
	{
		IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(Target.Get());
		if (ASI)
		{
			// Attribute Effect
			UAbilitySystemComponent* TargetASC = ASI->GetAbilitySystemComponent();
			if (!TargetASC)
			{
				UE_LOG(LogTemp, Warning, TEXT("Unvalid Target ASC"));
				continue;
			}
			FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffectClass);
			if (EffectSpecHandle.IsValid())
			{ 
				UE_LOG(LogTemp, Warning, TEXT("Apply Damage To Target"));

				SourceASC->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), TargetASC);
			}

			// Game play Cue
			TargetASC->ExecuteGameplayCue(CueTag);
		}
	}
}

void UPRGA_DefaultAttack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

}

void UPRGA_DefaultAttack::OnSkillMontageComplete()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UPRGA_DefaultAttack::OnSkillMontageInterrupted()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
