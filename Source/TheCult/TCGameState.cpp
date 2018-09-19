// Fill out your copyright notice in the Description page of Project Settings.

#include "TCGameState.h"
#include "TCPlayerState.h"
#include "UnrealNetwork.h"

ATCGameState::ATCGameState()
{
	bReplicates = true;
}

void ATCGameState::KillSurvivors(int32 KilledSurvivors)
{
	Survivors -= KilledSurvivors;
	UE_LOG(LogTemp, Warning, TEXT("Killed %d survivors!"), KilledSurvivors);
}

void ATCGameState::BeginPlay()
{
	Super::BeginPlay();


}

void ATCGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATCGameState, Survivors);
	DOREPLIFETIME(ATCGameState, Heat);
	DOREPLIFETIME(ATCGameState, LastNews);
	DOREPLIFETIME(ATCGameState, CurrentDay);
}

void ATCGameState::AttackSurvivors(int32 Strength, ATCPlayerState* PlayerState)
{
	if (!HasAuthority())
	{
		return;
	}

	if (PlayerState && PlayerState->ConsumeActionPoints(AttackPrice))
	{
		int32 KilledSurvivors = FMath::RandRange(Strength / 4.0f, Strength * 1.5f);
		KilledSurvivors = FMath::Clamp(KilledSurvivors, 0, Survivors);

		AddNews(FString("The cult attacks again! Survivors killed: " + FString::FromInt(KilledSurvivors)));

		KillSurvivors(KilledSurvivors);

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
			if (TCPlayerState->bIsLockdown)
			{
				continue;
			}

			float KilledSurvivors = FMath::RandRange(1, TCPlayerState->Followers / 4);
			
			TCPlayerState->KillFollowers(FMath::TruncToInt(KilledSurvivors));
			TotalCasualities += FMath::TruncToInt(KilledSurvivors);
		}
	}

	AddNews(FString("Survivors raided a cult hideout! Killed: " + FString::FromInt(TotalCasualities)));
}

void ATCGameState::IncreasePopulation()
{
	float AdultWomanSurvivors = (Survivors / 100 * 60) / 2;

	int32 PopulationIncrease = FMath::TruncToInt(AdultWomanSurvivors / 100 * FMath::RandRange(0.1f, 2.0f));

	AddNews(FString("Population increased: " + FString::FromInt(PopulationIncrease)));

	Survivors += PopulationIncrease;
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