// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/PRGA_CastSkill.h"
#include "Battle/PRBattleLevelManager.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Data/PRSkillData.h"
#include "SkillAbility/PRGA_SkillAbilityBase.h"


UPRGA_CastSkill::UPRGA_CastSkill()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

}

void UPRGA_CastSkill::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

}

void UPRGA_CastSkill::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UE_LOG(LogTemp, Warning, TEXT("Cast Skill Ability"));

	// Input ID 기반 스킬 라우팅
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	if (!ASC) 
	{ 
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
		return; 
	}
	
	if (!TriggerEventData)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
		return;
	}

	const USkillData* Data = Cast<USkillData>(TriggerEventData->OptionalObject);
	if (!Data)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
		return;
	}

	FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromInputID(Data->InputType);
	if (!Spec)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
		return;
	}

	RoutedSpecHandle = Spec->Handle;

	if (!AbilityEndedHandle.IsValid())
	{
		AbilityEndedHandle = ASC->OnAbilityEnded.AddUObject(this, &UPRGA_CastSkill::OnSkillComplete);
	}

	// Cast Event Tag로 이벤트 재전송
	UPRGA_SkillAbilityBase* SkillAbility = Cast<UPRGA_SkillAbilityBase>(Spec->Ability);
	if (SkillAbility)
	{
		FGameplayEventData Fwd = *TriggerEventData;
		Fwd.EventTag = SkillAbility->GetEventTag();
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(ActorInfo->AvatarActor.Get(), SkillAbility->GetEventTag(), Fwd);
	}
}

void UPRGA_CastSkill::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

}


void UPRGA_CastSkill::OnSkillComplete(const FAbilityEndedData& Data)
{
	if (Data.AbilitySpecHandle != RoutedSpecHandle)
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Skill Completed"));

	// 델리게이트 Unbind
	if (UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo())
	{
		if (AbilityEndedHandle.IsValid())
		{
			ASC->OnAbilityEnded.Remove(AbilityEndedHandle);
			AbilityEndedHandle.Reset();
		}
	}

	RoutedSpecHandle = FGameplayAbilitySpecHandle();

	APRBattleLevelManager* Manager = APRBattleLevelManager::Get(GetWorld());

	if (Manager)
	{
		Manager->OnExecuteCommand();
	}

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
