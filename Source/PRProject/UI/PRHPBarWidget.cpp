// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PRHPBarWidget.h"
#include "PRHPBarWidget.h"
#include "Components/ProgressBar.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Attributes/PRCombatAttributeSet.h"
#include "GameplayEffectExtension.h"

void UPRHPBarWidget::InitFromASC(UAbilitySystemComponent* InASC)
{
	// 이전 바인딩 정리
	UnbindAttributeDelegates();

	if (!IsValid(InASC))
	{
		ASCWeak.Reset();
		return;
	}

	ASCWeak = InASC;

	// 초기값 읽고 표시
	PullInitialValues();
	UpdateFromAttributes();

	// 변경 델리게이트 바인딩
	BindAttributeDelegates();
}

void UPRHPBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPRHPBarWidget::NativeDestruct()
{
	UnbindAttributeDelegates();
	Super::NativeDestruct();
}

void UPRHPBarWidget::UpdateFromAttributes()
{
	if (!HPBar) return;
	const float Percent = (CachedMaxHealth > 0.f) ? (CachedHealth / CachedMaxHealth) : 0.f;
	HPBar->SetPercent(Percent);
}

void UPRHPBarWidget::BindAttributeDelegates()
{
	if (UAbilitySystemComponent* ASC = ASCWeak.Get())
	{
		// Health 변경 델리게이트
		HealthChangedHandle = ASC->GetGameplayAttributeValueChangeDelegate(
			UPRCombatAttributeSet::GetHealthAttribute())
			.AddUObject(this, &UPRHPBarWidget::OnHealthChanged);

		// MaxHealth 변경 델리게이트
		MaxHealthChangedHandle = ASC->GetGameplayAttributeValueChangeDelegate(
			UPRCombatAttributeSet::GetMaxHealthAttribute())
			.AddUObject(this, &UPRHPBarWidget::OnMaxHealthChanged);
	}
}

void UPRHPBarWidget::UnbindAttributeDelegates()
{
	if (UAbilitySystemComponent* ASC = ASCWeak.Get())
	{
		if (HealthChangedHandle.IsValid())
		{
			ASC->GetGameplayAttributeValueChangeDelegate(
				UPRCombatAttributeSet::GetHealthAttribute()).Remove(HealthChangedHandle);
			HealthChangedHandle.Reset();
		}
		if (MaxHealthChangedHandle.IsValid())
		{
			ASC->GetGameplayAttributeValueChangeDelegate(
				UPRCombatAttributeSet::GetMaxHealthAttribute()).Remove(MaxHealthChangedHandle);
			MaxHealthChangedHandle.Reset();
		}
	}
}

void UPRHPBarWidget::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	CachedHealth = Data.NewValue;
	UpdateFromAttributes();
}

void UPRHPBarWidget::OnMaxHealthChanged(const FOnAttributeChangeData& Data)
{
	CachedMaxHealth = Data.NewValue;
	UpdateFromAttributes();
}

void UPRHPBarWidget::PullInitialValues()
{
	if (UAbilitySystemComponent* ASC = ASCWeak.Get())
	{
		CachedHealth = ASC->GetNumericAttribute(UPRCombatAttributeSet::GetHealthAttribute());
		CachedMaxHealth = ASC->GetNumericAttribute(UPRCombatAttributeSet::GetMaxHealthAttribute());
	}
	else
	{
		CachedHealth = 0.f;
		CachedMaxHealth = 0.f;
	}
}
