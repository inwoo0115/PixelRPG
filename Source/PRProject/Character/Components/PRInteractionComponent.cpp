// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Components/PRInteractionComponent.h"
#include "PRInteractionComponent.h"
#include "Interface/PRInteractableInterface.h"

UPRInteractionComponent::UPRInteractionComponent()
{
}


void UPRInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPRInteractionComponent::Interact()
{
	AActor* Owner = GetOwner();

	if (!Owner || Candidates.Num() == 0)
	{
		return;
	}

	float Distance = MAX_FLT;
	AActor* SelectedActor = nullptr;

	for (AActor* Candidate : Candidates)
	{
		if (!Candidate) continue;

		float CurrentDistance = Candidate->GetDistanceTo(Owner);
		if (CurrentDistance < Distance)
		{
			Distance = CurrentDistance;
			SelectedActor = Candidate;
		}
	}

	if (SelectedActor && SelectedActor->Implements<UPRInteractableInterface>())
	{
		IPRInteractableInterface* InteractActor = Cast<IPRInteractableInterface>(SelectedActor);
		InteractActor->Interact(Owner);
	}
}

void UPRInteractionComponent::AddCandidate(AActor* NewCandidate)
{
	if (NewCandidate->Implements<UPRInteractableInterface>())
	{
		Candidates.Add(NewCandidate);
	}
}

void UPRInteractionComponent::RemoveCandidate(AActor* DeleteCandidate)
{
	if (!DeleteCandidate->Implements<UPRInteractableInterface>())
	{
		return;
	}

	Candidates.Remove(DeleteCandidate);
}


