// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/PRInteractionActorBase.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "Interface/PRInteractComponentInterface.h"
#include "Character/Components/PRInteractionComponent.h"


// Sets default values
APRInteractionActorBase::APRInteractionActorBase()
{
	PrimaryActorTick.bCanEverTick = false;

	// ¹Ú½º ÄÄÆ÷³ÍÆ® ¼³Á¤
	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	RootComponent = InteractionBox;
	InteractionBox->SetBoxExtent(FVector(100.f, 100.f, 100.f));
	InteractionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	InteractionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	// À§Á¬ ÄÄÆ÷³ÍÆ®
	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
	InteractionWidget->SetupAttachment(RootComponent);
	InteractionWidget->SetWidgetSpace(EWidgetSpace::Screen);
	InteractionWidget->SetDrawSize(FVector2D(200, 50));
	InteractionWidget->SetVisibility(false); // Ã³À½¿¡´Â ¼û±è
}

void APRInteractionActorBase::Interact(AActor* InteractActor)
{
	if (bCanInteract)
	{
		// interact logic
		// UE_LOG(LogTemp, Warning, TEXT("Interact"));
	}
}

void APRInteractionActorBase::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->Implements<UPRInteractComponentInterface>())
	{
		bCanInteract = true;
		InteractionWidget->SetVisibility(true);

		IPRInteractComponentInterface* ICI = Cast<IPRInteractComponentInterface>(OtherActor);
		ICI->GetInteractionComponent()->AddCandidate(this);
	}
}

void APRInteractionActorBase::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->Implements<UPRInteractComponentInterface>())
	{
		bCanInteract = false;
		InteractionWidget->SetVisibility(false);

		IPRInteractComponentInterface* ICI = Cast<IPRInteractComponentInterface>(OtherActor);
		ICI->GetInteractionComponent()->RemoveCandidate(this);
	}
}


void APRInteractionActorBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (InteractionBox)
	{
		InteractionBox->OnComponentBeginOverlap.AddDynamic(this, &APRInteractionActorBase::OnBoxBeginOverlap);
		InteractionBox->OnComponentEndOverlap.AddDynamic(this, &APRInteractionActorBase::OnBoxEndOverlap);
	}
}
