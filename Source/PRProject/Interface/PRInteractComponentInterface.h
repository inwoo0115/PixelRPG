// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PRInteractComponentInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPRInteractComponentInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PRPROJECT_API IPRInteractComponentInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual class UPRInteractionComponent* GetInteractionComponent() = 0;
};
