// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PRCharacterBase.h"
#include "InputAction.h"
#include "PRPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PRPROJECT_API APRPlayerCharacter : public APRCharacterBase
{
	GENERATED_BODY()
	
public:
	APRPlayerCharacter();

	void Move(const FInputActionValue& Value);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputAction> MoveAction;

};
