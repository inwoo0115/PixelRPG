// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Task/PRAT_PlaySequenceAndWait.h"
#include "Animation/PRAnimInstance.h"
#include "PaperZDCharacter.h"
#include "PRAT_PlaySequenceAndWait.h"

UPRAT_PlaySequenceAndWait* UPRAT_PlaySequenceAndWait::CreatePlaySequenceAndWaitProxy(UGameplayAbility* OwningAbility, FName TaskInstanceName, UPaperZDAnimSequence* SequenceToPlay, float Rate, FName SlotName, float StartPosition)
{
	UPRAT_PlaySequenceAndWait* Task = NewAbilityTask<UPRAT_PlaySequenceAndWait>(OwningAbility, TaskInstanceName);
	Task->AnimToPlay = SequenceToPlay;
	Task->Rate = Rate;
	Task->SlotName = SlotName;
	Task->StartPosition = StartPosition;

	return Task;
}

void UPRAT_PlaySequenceAndWait::Activate()
{
	if (!Ability || !AnimToPlay)
	{
		EndTask();
		return;
	}

	AActor* AvatarActor = GetAvatarActor();
	if (!AvatarActor)
	{
		EndTask();
		return;
	}

	APaperZDCharacter* Character = Cast<APaperZDCharacter>(AvatarActor);
	if (Character)
	{
		AnimInstance = Character->GetAnimInstance();
	}

	if (!AnimInstance)
	{
		EndTask();
		return;
	}

	// Sequence End Delegate
	FZDOnAnimationOverrideEndSignature SequenceEnd;
	SequenceEnd.BindUObject(this, &UPRAT_PlaySequenceAndWait::OnAnimEnd);

	// 애니메이션 재생
	bPlayValid = AnimInstance->PlayAnimationOverride(AnimToPlay, SlotName, Rate, StartPosition, SequenceEnd);

	if (!bPlayValid)
	{
		EndTask();
	}
}

void UPRAT_PlaySequenceAndWait::OnDestroy(bool bInOwnerFinished)
{
	if (bPlayValid && AnimInstance)
	{
		AnimInstance->StopAllAnimationOverrides();

		if (ShouldBroadcastAbilityTaskDelegates())
		{
			OnInterrupted.Broadcast();
		}
	}

	Super::OnDestroy(bInOwnerFinished);
}

void UPRAT_PlaySequenceAndWait::OnAnimEnd(bool bCompleted)
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnCompleted.Broadcast();
	}
	EndTask();
}
