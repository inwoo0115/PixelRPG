// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PRCharacterBase.h"
#include "InputAction.h"
#include "Interface/PRInteractComponentInterface.h"
#include "PRPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PRPROJECT_API APRPlayerCharacter : public APRCharacterBase, public IPRInteractComponentInterface
{
	GENERATED_BODY()
	
public:
	APRPlayerCharacter();

	// Input Action Functions
	void Move(const FInputActionValue& Value);

	void Interact(const FInputActionValue& Value);

	// Input setting
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual class UPRInteractionComponent* GetInteractionComponent() override;

protected:
	// Input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputAction> InteractAction;

	// Components
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	TObjectPtr<class UPRInteractionComponent> InteractionComponent;

};
