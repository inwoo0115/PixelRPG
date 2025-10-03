// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/PRNonPlayerCharacterBase.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Interface/PRInteractComponentInterface.h"
#include "Character/Components/PRInteractionComponent.h"

APRNonPlayerCharacterBase::APRNonPlayerCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// �ڽ� ������Ʈ ����
	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	RootComponent = InteractionBox;
	InteractionBox->SetBoxExtent(FVector(100.f, 100.f, 100.f));
	InteractionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	InteractionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	// ���� ������Ʈ
	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
	InteractionWidget->SetupAttachment(RootComponent);
	InteractionWidget->SetWidgetSpace(EWidgetSpace::Screen);
	InteractionWidget->SetDrawSize(FVector2D(200, 50));
	InteractionWidget->SetVisibility(false);
}

void APRNonPlayerCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void APRNonPlayerCharacterBase::Interact(AActor* InteractActor)
{
	if (bCanInteract)
	{
		// ���⿡ ���� ����
	}
}

void APRNonPlayerCharacterBase::CollisionEvent(AActor* InteractActor)
{
	// �浹 �� �̺�Ʈ ����
}

void APRNonPlayerCharacterBase::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// �浹 �� �̺�Ʈ�� ���� ��� �켱 ȣ��
	if (bHasCollisionEvent && bCanCollisionEvent)
	{
		CollisionEvent(OtherActor);
		bCanCollisionEvent = false;
		return;
	}

	if (OtherActor && OtherActor->Implements<UPRInteractComponentInterface>())
	{
		bCanInteract = true;
		if (InteractionWidget)
		{
			InteractionWidget->SetVisibility(true);
		}
		IPRInteractComponentInterface* ICI = Cast<IPRInteractComponentInterface>(OtherActor);
		ICI->GetInteractionComponent()->AddCandidate(this);
	}
}

void APRNonPlayerCharacterBase::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->Implements<UPRInteractComponentInterface>())
	{
		bCanInteract = false;
		if (InteractionWidget)
		{
			InteractionWidget->SetVisibility(false);
		}
		IPRInteractComponentInterface* ICI = Cast<IPRInteractComponentInterface>(OtherActor);
		ICI->GetInteractionComponent()->RemoveCandidate(this);
	}

	bCanCollisionEvent = true;
}