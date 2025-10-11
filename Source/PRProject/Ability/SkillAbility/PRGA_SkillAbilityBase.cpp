// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/SkillAbility/PRGA_SkillAbilityBase.h"

FGameplayTag UPRGA_SkillAbilityBase::GetEventTag() const
{
	return EventTag;
}

FText UPRGA_SkillAbilityBase::GetSkillName() const
{
	return SkillName;
}
