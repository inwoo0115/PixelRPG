// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/PREnemyBase.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "Attributes/PRCombatAttributeSet.h"
#include "UI/PRHPBarWidget.h"
#include "Components/WidgetComponent.h"


APREnemyBase::APREnemyBase()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));

	CombatAttribute = CreateDefaultSubobject<UPRCombatAttributeSet>(TEXT("CombatAttribute"));

	HPBarComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBar"));
	HPBarComp->SetupAttachment(RootComponent);
}

void APREnemyBase::BeginPlay()
{
	Super::BeginPlay();

	if (ASC)
	{
		ASC->InitAbilityActorInfo(this, this);

		// Ability µî·Ï
		for (const auto& StartAbility : StartAbilities)
		{
			FGameplayAbilitySpec StartSpec(StartAbility);
			ASC->GiveAbility(StartSpec);
		}

		for (const auto& SkillAbility : SkillAbilities)
		{
			FGameplayAbilitySpec StartSpec(SkillAbility.Value);
			StartSpec.InputID = (int32)(SkillAbility.Key);
			ASC->GiveAbility(StartSpec);
		}
	}

	if (HPBarComp && HPBarComp->GetUserWidgetObject())
	{
		if (auto* HPW = Cast<UPRHPBarWidget>(HPBarComp->GetUserWidgetObject()))
		{
			HPW->InitFromASC(ASC);
		}
	}
}

UAbilitySystemComponent* APREnemyBase::GetAbilitySystemComponent() const
{
	return ASC;
}

float APREnemyBase::GetSpeed()
{
	if (ASC->GetSet<UPRCombatAttributeSet>())
	{
		return ASC->GetSet<UPRCombatAttributeSet>()->GetSpeed();
	}
	return 0.0f;
}

bool APREnemyBase::IsAlive()
{
	if (ASC->GetSet<UPRCombatAttributeSet>())
	{
		if (ASC->GetSet<UPRCombatAttributeSet>()->GetHealth() <= 0.0f)
		{
			return false;
		}
	}

	return true;
}
