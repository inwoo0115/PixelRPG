// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "Interface/PRInteractableInterface.h"
#include "PRNonPlayerCharacterBase.generated.h"

/**
 * 
 */
UCLASS()
class PRPROJECT_API APRNonPlayerCharacterBase : public APaperZDCharacter, public IPRInteractableInterface
{
	GENERATED_BODY()

public:
	APRNonPlayerCharacterBase();

	virtual void BeginPlay() override;

	// 상호 작용 오브젝트 별 interaction 가상 함수
	virtual void Interact(AActor* InteractActor) override;

	virtual void CollisionEvent(AActor* InteractActor);

	// 오버랩 이벤트 함수
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	TObjectPtr<class UBoxComponent> InteractionBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	TObjectPtr<class UWidgetComponent> InteractionWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	bool bCanInteract = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	bool bCanCollisionEvent = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	bool bHasCollisionEvent = false;
};
