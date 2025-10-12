// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Cue/PRGC_DefaultAttackEffect.h"
#include "Kismet/GameplayStatics.h"

UPRGC_DefaultAttackEffect::UPRGC_DefaultAttackEffect()
{
}

bool UPRGC_DefaultAttackEffect::OnExecute_Implementation(AActor* Target, const FGameplayCueParameters& Parameters) const
{
	UGameplayStatics::SpawnEmitterAtLocation(Target, ParticleSystem, Target->GetActorLocation(), FRotator::ZeroRotator, true);
	return false;
}
