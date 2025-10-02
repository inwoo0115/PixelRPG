// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"
#include "PRBattleManager.generated.h"

UCLASS()
class PRPROJECT_API APRBattleManager : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	APRBattleManager();

    static APRBattleManager* Get(UWorld* World);

    virtual void BeginPlay() override;

    virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

private:
    static APRBattleManager* Singleton;

	// GAS
	UPROPERTY(EditAnywhere, Category = "GAS")
	TArray<TSubclassOf<class UGameplayAbility>> StartAbilties;

	UPROPERTY(EditAnywhere, Category = "GAS")
	TObjectPtr<class UAbilitySystemComponent> ASC;

};
