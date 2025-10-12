// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/SkillAbility/PRGA_SkillAbilityBase.h"
#include "Battle/PRBattleLevelManager.h"


UPRGA_SkillAbilityBase::UPRGA_SkillAbilityBase()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

}

FGameplayTag UPRGA_SkillAbilityBase::GetEventTag() const
{
	return EventTag;
}

FText UPRGA_SkillAbilityBase::GetSkillName() const
{
	return SkillName;
}
