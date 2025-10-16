// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/PRNonPlayerCharacterBase.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Interface/PRInteractComponentInterface.h"
#include "Character/Components/PRInteractionComponent.h"
#include "Battle/PRBattleManager.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Data/PRBattleDataAsset.h"

APRNonPlayerCharacterBase::APRNonPlayerCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// 박스 컴포넌트 설정
	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetupAttachment(RootComponent);;
	InteractionBox->SetBoxExtent(FVector(100.f, 100.f, 100.f));
	InteractionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	InteractionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	// 위젯 컴포넌트
	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
	InteractionWidget->SetupAttachment(RootComponent);
	InteractionWidget->SetWidgetSpace(EWidgetSpace::Screen);
	InteractionWidget->SetDrawSize(FVector2D(200, 50));
	InteractionWidget->SetVisibility(false);
}

void APRNonPlayerCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if (InteractionBox)
	{
		InteractionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &APRNonPlayerCharacterBase::OnBoxBeginOverlap);
		InteractionBox->OnComponentEndOverlap.AddUniqueDynamic(this, &APRNonPlayerCharacterBase::OnBoxEndOverlap);
	}
}

void APRNonPlayerCharacterBase::Interact(AActor* InteractActor)
{
	if (bCanInteract)
	{
		// 전투 시작
		APRBattleManager* BM = APRBattleManager::Get(GetWorld());
		if (!BM)
		{
			return;
		}

		FGameplayEventData Data;
		Data.EventTag = CreateBattleTag;
		Data.Instigator = InteractActor;
		Data.Target = BM;
		Data.OptionalObject = BattleData;

		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(BM, CreateBattleTag, Data);
	}
}

void APRNonPlayerCharacterBase::CollisionEvent(AActor* InteractActor)
{
	// 전투 시작
	APRBattleManager* BM = APRBattleManager::Get(GetWorld());
	if (!BM)
	{
		return;
	}

	FGameplayEventData Data;
	Data.EventTag = CreateBattleTag;
	Data.Instigator = InteractActor;
	Data.Target = BM;
	Data.OptionalObject = BattleData;

	bBattleEventFinished = true;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(BM, CreateBattleTag, Data);
}

void APRNonPlayerCharacterBase::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 충돌 시 이벤트가 있을 경우 우선 호출
	if (bHasCollisionEvent && bCanCollisionEvent &&!bBattleEventFinished)
	{
		if (OtherActor->Implements<UPRInteractComponentInterface>())
		{
			CollisionEvent(OtherActor);
			bCanCollisionEvent = false;
		}
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