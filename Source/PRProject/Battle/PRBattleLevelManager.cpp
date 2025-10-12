// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/PRBattleLevelManager.h"
#include "Battle/PRBattleManager.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interface/PRBattleInterface.h"
#include "Kismet/GameplayStatics.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Character/PRCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "Attributes/PRCombatAttributeSet.h"

APRBattleLevelManager* APRBattleLevelManager::Singleton = nullptr;

APRBattleLevelManager::APRBattleLevelManager()
{
	PrimaryActorTick.bCanEverTick = true;

	// Camera, Spring Arm 설정
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

}

APRBattleLevelManager* APRBattleLevelManager::Get(UWorld* World)
{
    if (Singleton)
    {
        return Singleton;
    }

    return Cast<APRBattleLevelManager>(UGameplayStatics::GetActorOfClass(World, APRBattleLevelManager::StaticClass()));
}

void APRBattleLevelManager::BeginPlay()
{
	Super::BeginPlay();

    Singleton = this;
}

void APRBattleLevelManager::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

}

void APRBattleLevelManager::InitBattle()
{
	GatherAliveParticipant();
	BuildTurnOrder();

    if (!Participants.Num())
    {
        return;
    }

    StartPhase(EBattlePhase::Intro);
}

void APRBattleLevelManager::GatherAliveParticipant()
{
	Participants.Empty();

	uint64 Index = 0;

	// Level에 있는 액터 수집
	TArray<AActor*> Cands;
	UGameplayStatics::GetAllActorsWithInterface(this, UPRBattleInterface::StaticClass(), Cands);

    for (AActor* A : Cands)
    {
        if (!IsValid(A)) continue;

        IPRBattleInterface* BI = Cast<IPRBattleInterface>(A);

        FParticipantState S;
        S.Actor = A;
        S.Speed = BI->GetSpeed();
        S.bAlive = BI->IsAlive();
		S.StableId = Index;
        S.bIsAlly = false;

        // 캐릭터 일 경우 동료 표시
        APRCharacterBase* PRCharacter = Cast<APRCharacterBase>(A);
        if (PRCharacter)
        {
            S.bIsAlly = true;
        }

        BindHealthDelegate(A);

		Index++;
        Participants.Add(S);
    }
}

void APRBattleLevelManager::BuildTurnOrder()
{
	for (FParticipantState& S : Participants)
	{
		S.TieRoll = FMath::Rand();
	}

	Participants.Sort(FParticipantState::SortPredicate);
}

void APRBattleLevelManager::StartPhase(EBattlePhase NewPhase)
{
    CurrentPhase = NewPhase;

    switch (CurrentPhase)
    {
    case EBattlePhase::Intro:
        PhaseIntro();
        break;

    case EBattlePhase::StartTurn:
        PhaseStartTurn();
        break;

    case EBattlePhase::AwaitCommand:
        PhaseAwaitCommand();
        break;

    case EBattlePhase::Execute:
        PhaseExecute();
        break;

    case EBattlePhase::EndTurn:
        PhaseEndTurn();
        break;

    case EBattlePhase::EndBattle:
        PhaseEndBattle();

    default:
        break;
    }
}

void APRBattleLevelManager::PhaseIntro()
{
    UE_LOG(LogTemp, Warning, TEXT("Intro"));
    // 배틀 컷씬 재생
    
    // 턴 시작으로 이동
    StartPhase(EBattlePhase::StartTurn);
}

void APRBattleLevelManager::PhaseStartTurn()
{
    UE_LOG(LogTemp, Warning, TEXT("Start Trun"));
    if (!Participants[CurrentIndex].bAlive)
    {
        StartPhase(EBattlePhase::EndTurn);
    }

    // 턴 시작 컷씬

    // 플레이어 일 경우 명령대기
    if (Participants[CurrentIndex].bIsAlly)
    {
        StartPhase(EBattlePhase::AwaitCommand);
    }
    // AI 일 경우 실행
    else
    {
        StartPhase(EBattlePhase::Execute);
    }
}

void APRBattleLevelManager::PhaseAwaitCommand()
{
    UE_LOG(LogTemp, Warning, TEXT("Await Command"));

    // Start turn 어빌리티 실행
    FGameplayEventData Data;
    Data.EventTag = StartTurnTag;
    Data.Instigator = this;
    Data.Target = Participants[CurrentIndex].Actor.Get();

    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Participants[CurrentIndex].Actor.Get(), StartTurnTag, Data);

    // 카메라 현재 턴 플레이어 고정

}

void APRBattleLevelManager::OnExecuteCommand()
{
    UE_LOG(LogTemp, Warning, TEXT("On Execute"));
    // 델리게이트로 커맨드 실행 후 처리
    StartPhase(EBattlePhase::EndTurn);
}

void APRBattleLevelManager::SetBattleResult(EBattleResult NewResult)
{
    Result = NewResult;
}

TArray<TWeakObjectPtr<AActor>> APRBattleLevelManager::GetAliveEnemies() const
{
    UE_LOG(LogTemp, Warning, TEXT("Get Alive Enemies"));

    TArray<TWeakObjectPtr<AActor>> EnemyResult;
    EnemyResult.Reserve(Participants.Num());

    for (const FParticipantState& P : Participants)
    {
        if (P.bAlive && !P.bIsAlly && P.Actor.IsValid())
        {
            EnemyResult.Add(P.Actor);
        }
    }

    return EnemyResult;
}

void APRBattleLevelManager::PhaseExecute()
{
    UE_LOG(LogTemp, Warning, TEXT("Phase Execute"));
    // 적 어빌리티 실행

    // 실행 후 전투 결과 처리
    StartPhase(EBattlePhase::EndTurn);
}

void APRBattleLevelManager::PhaseEndTurn()
{
    UE_LOG(LogTemp, Warning, TEXT("End Turn"));
    // 배틀 결과 검사
    bool BattleResult = CheckBattleResult();

    // 배틀 지속 일 경우 다음 캐릭터 턴 시작으로 이동
    if (!BattleResult)
    {
        CurrentIndex++;
        if (Participants.Num() <= CurrentIndex)
        {
            BuildTurnOrder();
            CurrentIndex = 0;
        }
        StartPhase(EBattlePhase::StartTurn);
    }
    // 결과가 나왔을 경우 배틀 종료 (도망치기, 승리, 패배)
    else
    {
        StartPhase(EBattlePhase::EndBattle);
    }
}

void APRBattleLevelManager::PhaseEndBattle()
{
    UE_LOG(LogTemp, Warning, TEXT("End Battle"));

    // 임시: 결과 텍스트 표시
    FString ResultText;

    switch (Result)
    {
        case EBattleResult::Victory:
            ResultText = TEXT("Victory");
            break;
        case EBattleResult::Defeat:
            ResultText = TEXT("Defeat");
            break;
        case EBattleResult::Runaway:
            ResultText = TEXT("Runaway");
            break;
        default:
            ResultText = TEXT("None");
    }

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(
            /*Key*/ -1,
            /*Time*/ 2.0f,
            /*Color*/ FColor(0, 200, 255),
            /*Message*/ ResultText
        );
    }

    // Battle Manager에 전투 결과 전송

    // End battle 어빌리티 호출
    FGameplayEventData Data;
    Data.EventTag = EndBattleTag;

    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(APRBattleManager::Get(GetWorld()), EndBattleTag, Data);
}

bool APRBattleLevelManager::CheckBattleResult()
{
    if (Result != EBattleResult::None)
    {
        return true;
    }

    bool bAnyAllyAlive = false;
    bool bAnyEnemyAlive = false;

    for (const FParticipantState& S : Participants)
    {
        if (!S.Actor.IsValid() || !S.bAlive)
            continue;

        if (S.bIsAlly)
            bAnyAllyAlive = true;
        else
            bAnyEnemyAlive = true;

        if (bAnyAllyAlive && bAnyEnemyAlive)
            return false;
    }

    if (!bAnyAllyAlive)
    {
        Result = EBattleResult::Defeat;
    }
    else if (!bAnyEnemyAlive)
    {
        Result = EBattleResult::Victory;
    }

    return (!bAnyAllyAlive || !bAnyEnemyAlive);
}

void APRBattleLevelManager::BindHealthDelegate(AActor* Actor)
{
    IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(Actor);
    
    if (!ASI) return;

    UAbilitySystemComponent* ASC = ASI->GetAbilitySystemComponent();

    // 기존 바인딩 있으면 해제
    UnbindHealthDelegate(ASC);

    TWeakObjectPtr<AActor> WeakActor = Actor;

    // Health 변경에 반응 → bAlive 갱신
    const FGameplayAttribute HealthAttr = UPRCombatAttributeSet::GetHealthAttribute();
    FDelegateHandle Handle = ASC->GetGameplayAttributeValueChangeDelegate(HealthAttr)
        .AddLambda([this, WeakActor](const FOnAttributeChangeData& Data)
            {
                AActor* A = WeakActor.Get();
                if (!A) return;

                const bool bAliveNew = (Data.NewValue > 0.f);
                SetAliveForActor(A, bAliveNew);
            });

    HealthHandles.Add(ASC, Handle);
}

void APRBattleLevelManager::UnbindHealthDelegate(UAbilitySystemComponent* ASC)
{
    if (!ASC) return;
    if (FDelegateHandle* Handle = HealthHandles.Find(ASC))
    {
        if (Handle->IsValid())
        {
            ASC->GetGameplayAttributeValueChangeDelegate(UPRCombatAttributeSet::GetHealthAttribute())
                .Remove(*Handle);
        }
        HealthHandles.Remove(ASC);
    }
}

void APRBattleLevelManager::SetAliveForActor(AActor* Actor, bool bAliveNew)
{
    const int32 Idx = FindParticipantIndex(Actor);
    if (Idx == INDEX_NONE) return;

    FParticipantState& P = Participants[Idx];
    if (P.bAlive != bAliveNew)
    {
        P.bAlive = bAliveNew;
    }
}

int32 APRBattleLevelManager::FindParticipantIndex(AActor* Actor) const
{
    for (int32 i = 0; i < Participants.Num(); ++i)
    {
        if (Participants[i].Actor.Get() == Actor)
        {
            return i;
        }
    }
    return INDEX_NONE;
}

