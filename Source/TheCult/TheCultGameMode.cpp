// Fill out your copyright notice in the Description page of Project Settings.

#include "TheCultGameMode.h"
#include "TCGameState.h"
#include "TCPlayerState.h"

void ATCGameMode::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("The Game begins."));

	GetWorld()->GetTimerManager().SetTimer(UpdateActionPointsTimer, this, &ATCGameMode::GiveActionPoints, APUpdateRate, true);

	GetWorld()->GetTimerManager().SetTimer(UpdateHeatTimer, this, &ATCGameMode::UpdateHeat, HeatUpdateRate, true);

	GetWorld()->GetTimerManager().SetTimer(UpdatePopulationTimer, this, &ATCGameMode::UpdatePopulation, PopulationUpdateRate, true);
}

void ATCGameMode::GiveActionPoints()
{
	for (auto PlayerState : GameState->PlayerArray)
	{
		ATCPlayerState* TCPlayerState = Cast<ATCPlayerState>(PlayerState);

		if (TCPlayerState)
		{
			if (TCPlayerState->ActionPoints < MaxAP)
			{
				TCPlayerState->AddActionPoint();
				TCPlayerState->MaxActionPoints = MaxAP;
			}
		}
	}
}

void ATCGameMode::UpdateHeat()
{
	ATCGameState* GameState = GetGameState<ATCGameState>();

	if (GameState)
	{
		if (GameState->Heat > HeatThresholdBeforeRetaliation)
		{
			if (FMath::RandBool())
			{
				GameState->RaidOnCultists();
				GameState->DecreaseHeat();
			}
		}
		else 
		{
			GameState->DecreaseHeat();
		}
	}
}

void ATCGameMode::UpdatePopulation()
{
	ATCGameState* GameState = GetGameState<ATCGameState>();

	if (GameState)
	{
		GameState->IncreasePopulation();
	}
}
