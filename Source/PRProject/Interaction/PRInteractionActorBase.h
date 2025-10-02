// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/PRInteractableInterface.h"
#include "PRInteractionActorBase.generated.h"

UCLASS()
class PRPROJECT_API APRInteractionActorBase : public AActor, public IPRInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APRInteractionActorBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// ��ȣ �ۿ� ������Ʈ �� interaction ���� �Լ�
	virtual void Interact(AActor* InteractActor) override;

	// ������ �̺�Ʈ �Լ�
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UBoxComponent> InteractionBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	TObjectPtr<class UWidgetComponent> InteractionWidget;

	bool bCanInteract = false;

};
