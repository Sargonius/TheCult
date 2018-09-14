// Fill out your copyright notice in the Description page of Project Settings.

#include "TheCultGameMode.h"
#include "TCGameState.h"
#include "TCPlayerState.h"

void ATCGameMode::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("GameMode BeginPlay Called, yay!"));

	GetWorld()->GetTimerManager().SetTimer(UpdateActionPointsTimer, this, &ATCGameMode::GiveActionPoints, 5.0f, true);

	GetWorld()->GetTimerManager().SetTimer(UpdateHeatTimer, this, &ATCGameMode::UpdateHeat, 30.0f, true);
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
			}
		}
	}
}

void ATCGameMode::UpdateHeat()
{
	ATCGameState* GameState = GetGameState<ATCGameState>();

	if (GameState)
	{
		GameState->DecreaseHeat();
	}
}

