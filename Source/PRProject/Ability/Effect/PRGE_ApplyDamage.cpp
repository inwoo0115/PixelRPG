// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Effect/PRGE_ApplyDamage.h"
#include "PRGE_ApplyDamage.h"
#include "Attributes/PRCombatAttributeSet.h"

UPRGE_ApplyDamage::UPRGE_ApplyDamage()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;
}
