// Fill out your copyright notice in the Description page of Project Settings.

#include "TCGameState.h"
#include "TCPlayerState.h"
#include "UnrealNetwork.h"
#include "Camp.h"

ATCGameState::ATCGameState()
{
	bReplicates = true;
}

ACamp* ATCGameState::GetCamp()
{
	return Camp;
}

void ATCGameState::KillSurvivors(int32 KilledSurvivors)
{
	Camp->Kill(KilledSurvivors);
	//Survivors -= KilledSurvivors;
	UE_LOG(LogTemp, Warning, TEXT("Killed %d survivors!"), KilledSurvivors);
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

void ATCGameState::AttackSurvivors(int32 KilledSurvivors, ATCPlayerState* PlayerState)
{
	if (PlayerState && PlayerState->ConsumeActionPoints(AttackPrice))
	{
		AddNews(FString("The cult attacks again! Survivors killed: " + FString::FromInt(KilledSurvivors)));

		Camp->Kill(KilledSurvivors);
		//KillSurvivors(KilledSurvivors);

		IncreaseHeat();
	}
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
	int32 TotalCasualities = 0;

	for (auto PlayerState : PlayerArray)
	{
		ATCPlayerState* TCPlayerState = Cast<ATCPlayerState>(PlayerState);
		if (TCPlayerState)
		{
			if (TCPlayerState->GetCamp()->bIsLockdown)
			{
				continue;
			}

			float KilledSurvivors = FMath::RandRange(1, TCPlayerState->GetCamp()->Population / 4);
			
			TCPlayerState->KillFollowers(FMath::TruncToInt(KilledSurvivors));
			TotalCasualities += FMath::TruncToInt(KilledSurvivors);
		}
	}

	AddNews(FString("Survivors raided a cult hideout! Killed: " + FString::FromInt(TotalCasualities)));
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

// Action - has price, handles action logic, checks AP