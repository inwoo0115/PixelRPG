// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PRPlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "AbilitySystemComponent.h"
#include "PaperZDAnimationComponent.h"
#include "PaperZDAnimInstance.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Character/Components/PRInteractionComponent.h"
#include "InputAction.h"

APRPlayerCharacter::APRPlayerCharacter()
{
	// Interaction
	InteractionComponent = CreateDefaultSubobject<UPRInteractionComponent>(TEXT("Interact"));
}

void APRPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		PlayerController->GetLocalPlayer()))
	{
		if (InputMappingContext)
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}

		if (IsValid(ASC) && IsValid(PlayerInputComponent))
		{
			UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APRPlayerCharacter::Move);
			EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &APRPlayerCharacter::Interact);
		}
	}
}

UPRInteractionComponent* APRPlayerCharacter::GetInteractionComponent()
{
	return InteractionComponent;
}

void APRPlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D Movement = Value.Get<FVector2D>();

	FRotator Rotation = GetActorRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	// 방향 구하기.
	FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X) * (-1);
	FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y) * (-1);

	AddMovementInput(ForwardVector, Movement.X);
	AddMovementInput(RightVector, Movement.Y);
}

void APRPlayerCharacter::Interact(const FInputActionValue& Value)
{
	if (InteractionComponent)
	{
		InteractionComponent->Interact();
	}
}
