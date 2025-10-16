// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "AbilitySystemInterface.h"
#include "Character/PRPlayerInputType.h"
#include "Interface/PRBattleInterface.h"
#include "PREnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class PRPROJECT_API APREnemyBase : public APaperZDCharacter, public IAbilitySystemInterface, public IPRBattleInterface
{
	GENERATED_BODY()

public:
	APREnemyBase();

	virtual void BeginPlay() override;

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// Battle Interface
	virtual float GetSpeed() override;
	virtual bool  IsAlive() override;

	virtual void InitByEnemyInfo(struct FEnemyInfo Info);

protected:
	// GAS
	UPROPERTY(EditAnywhere, Category = "GAS")
	TArray<TSubclassOf<class UGameplayAbility>> StartAbilities;

	UPROPERTY(EditAnywhere, Category = "GAS")
	TMap<EInputType, TSubclassOf<class UGameplayAbility>> SkillAbilities;

	UPROPERTY(EditAnywhere, Category = "GAS")
	TObjectPtr<class UAbilitySystemComponent> ASC;

	UPROPERTY(EditAnywhere, Category = "GAS")
	TObjectPtr<class UPRCombatAttributeSet> CombatAttribute;

	// Attribute Data
	UPROPERTY(EditDefaultsOnly, Category = "GAS")
	TObjectPtr<class UDataTable> DefaultAttributesDT;

	// 임시 체력 바
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class UWidgetComponent> HPBarComp;
};
