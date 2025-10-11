// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "AbilitySystemInterface.h"
#include "PRPlayerInputType.h"
#include "PRCharacterBase.generated.h"

/**
 * 
 */
UCLASS()
class PRPROJECT_API APRCharacterBase : public APaperZDCharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	APRCharacterBase();

	virtual void PossessedBy(AController* NewController) override;

	virtual void BeginPlay() override;

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	void SetAnimData(TObjectPtr<class UPRAnimationDataAsset> NewAnimData);

	const TMap<EInputType, TSubclassOf<class UGameplayAbility>> GetSkillAbilities();

protected:
	// GAS
	UPROPERTY(EditAnywhere, Category = "GAS")
	TArray<TSubclassOf<class UGameplayAbility>> StartAbilities;

	UPROPERTY(EditAnywhere, Category = "GAS")
	TMap<EInputType, TSubclassOf<class UGameplayAbility>> SkillAbilities;

	UPROPERTY(EditAnywhere, Category = "GAS")
	TMap<EInputType, TSubclassOf<class UGameplayAbility>> StartInputAbilties;

	UPROPERTY(EditAnywhere, Category = "GAS")
	TObjectPtr<class UAbilitySystemComponent> ASC;

	UPROPERTY(EditAnywhere, Category = "GAS")
	TArray<TSubclassOf<class UAttributeSet>> Attributes;

	// Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> SpringArm;

	// Animation
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimationData")
	TObjectPtr<class UPRAnimationDataAsset> AnimData;
};
