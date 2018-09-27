// Fill out your copyright notice in the Description page of Project Settings.

#include "TCGameState.h"
#include "TCPlayerState.h"
#include "UnrealNetwork.h"
#include "Camp.h"
#include "Actions/TCActionAttackOnCult.h"
#include "TimerManager.h"

ATCGameState::ATCGameState()
{
	bReplicates = true;

	AttackOnCultAction = CreateDefaultSubobject<UTCActionAttackOnCult>("AttackOnCultAction");
}

ACamp* ATCGameState::GetCamp()
{
	return Camp;
}

void ATCGameState::BeginPlay()
{
	Super::BeginPlay();
}

void ATCGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATCGameState, Camp);
	DOREPLIFETIME(ATCGameState, Heat);
	DOREPLIFETIME(ATCGameState, LastNews);
	DOREPLIFETIME(ATCGameState, CurrentDay);
}

void ATCGameState::IncreaseHeat()
{
	if (HasAuthority())
	{
		Heat += FMath::RandRange(0.01f, 0.1f);
		Heat = FMath::Clamp(Heat, 0.0f, 1.0f);
	}
}

void ATCGameState::DecreaseHeat()
{
	if (HasAuthority())
	{
		Heat -= FMath::RandRange(0.01f, 0.08f);
		Heat = FMath::Clamp(Heat, 0.0f, 1.0f);
		UE_LOG(LogTemp, Warning, TEXT("Heat decreased to %f"), Heat);
	}
}

void ATCGameState::RaidOnCultists()
{
	AttackOnCultAction->ActivateActionWithoutChecks();
}

void ATCGameState::IncreasePopulation()
{
	float AdultWomanSurvivors = (GetCamp()->Population / 100 * 60) / 2;

	int32 PopulationIncrease = FMath::TruncToInt(AdultWomanSurvivors / 100 * FMath::RandRange(0.1f, 2.0f));

	AddNews(FString("Population increased: " + FString::FromInt(PopulationIncrease)));

	GetCamp()->IncreasePopulation(PopulationIncrease);
}

void ATCGameState::AddNews(FString NewsToAdd)
{
	LastNews.Add(NewsToAdd);
	UE_LOG(LogTemp, Warning, TEXT("News: %s"), *NewsToAdd);
	if (LastNews.Num() > 5)
	{
		LastNews.RemoveAt(0);
	}
}
