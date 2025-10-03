// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PRAnimInstance.h"
#include "Character/PRPlayerCharacter.h"
#include "Animation/PRAnimationDataAsset.h"

void UPRAnimInstance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetPaperCharacter())
	{
		APRPlayerCharacter* Char = Cast<APRPlayerCharacter>(GetPaperCharacter());
		if (Char)
		{
			Velocity = Char->GetActorTransform().InverseTransformVector(Char->GetVelocity().GetSafeNormal(0.0001));

			if (Velocity.Length() > 0)
			{
				LastVelocity = Velocity;
			}
		}
	}
}

void UPRAnimInstance::SetAnimationData(UPRAnimationDataAsset* NewData)
{
	AnimData = NewData;
}

FVector UPRAnimInstance::GetLastVelocity() const
{
	return LastVelocity;
}
