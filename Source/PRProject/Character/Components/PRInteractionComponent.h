// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PRInteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PRPROJECT_API UPRInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPRInteractionComponent();

	void Interact();

	void AddCandidate(AActor* NewCandidate);

	void RemoveCandidate(AActor* DeleteCandidate);

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<TObjectPtr<AActor>> Candidates;
		
};
