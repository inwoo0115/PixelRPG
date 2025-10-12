// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayEffectTypes.h"
#include "PRHPBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class PRPROJECT_API UPRHPBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "HPBar")
	void InitFromASC(class UAbilitySystemComponent* InASC);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION(BlueprintCallable, Category = "HPBar")
	void UpdateFromAttributes();

	UFUNCTION(BlueprintPure, Category = "HPBar")
	float GetHealthPercent() const { return CachedMaxHealth > 0.f ? CachedHealth / CachedMaxHealth : 0.f; }


protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UProgressBar> HPBar;

	TWeakObjectPtr<UAbilitySystemComponent> ASCWeak;

	FDelegateHandle HealthChangedHandle;
	FDelegateHandle MaxHealthChangedHandle;

	UPROPERTY(Transient) 
	float CachedHealth = 0.f;

	UPROPERTY(Transient)
	float CachedMaxHealth = 0.f;

	void BindAttributeDelegates();
	void UnbindAttributeDelegates();

	void OnHealthChanged(const FOnAttributeChangeData& Data);
	void OnMaxHealthChanged(const FOnAttributeChangeData& Data);

	void PullInitialValues();
};
