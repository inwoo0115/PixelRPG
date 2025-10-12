// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PRCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "Player/PRPlayerState.h"
#include "GameplayAbilitySpec.h"
#include "Abilities/GameplayAbility.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Animation/PRAnimInstance.h"
#include "Attributes/PRCombatAttributeSet.h"

APRCharacterBase::APRCharacterBase()
{
	ASC = nullptr;

	//무브먼트 설정
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 360.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 400.0f;
	GetCharacterMovement()->bEnablePhysicsInteraction = false;

	// Camera, Spring Arm 설정
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void APRCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Player State Ability Component 적용
	APRPlayerState* PS = GetPlayerState<APRPlayerState>();
	if (PS)
	{
		ASC = PS->GetAbilitySystemComponent();
		ASC->InitAbilityActorInfo(PS, this);

		// Ability 등록
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

		// Input Ability 등록
		for (const auto& StartInputAbility : StartInputAbilties)
		{
			FGameplayAbilitySpec StartSpec(StartInputAbility.Value);
			StartSpec.InputID = (int32)(StartInputAbility.Key);
			ASC->GiveAbility(StartSpec);
		}

		// Attribute 초기화
		if (DefaultAttributesDT)
		{
			ASC->InitStats(UPRCombatAttributeSet::StaticClass(), DefaultAttributesDT);
		}
	}
}

void APRCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	// 애니메이션 data asset 적용
	if (AnimData)
	{
		SetAnimData(AnimData);
	}
}

void APRCharacterBase::SetAnimData(TObjectPtr<class UPRAnimationDataAsset> NewAnimData)
{
	UPRAnimInstance* AnimInst = Cast<UPRAnimInstance>(GetAnimInstance());
	if (AnimInst)
	{
		AnimInst->SetAnimationData(NewAnimData);
	}
}

const TMap<EInputType, TSubclassOf<class UGameplayAbility>> APRCharacterBase::GetSkillAbilities()
{
	return SkillAbilities;
}

void APRCharacterBase::SetLastVelocityByVector(FVector InVelocity)
{
	UPRAnimInstance* AnimInst = Cast<UPRAnimInstance>(GetAnimInstance());
	if (AnimInst)
	{
		AnimInst->SetLastVelocity(InVelocity);
	}
}


UAbilitySystemComponent* APRCharacterBase::GetAbilitySystemComponent() const
{
	return ASC;
}

