// Fill out your copyright notice in the Description page of Project Settings.

#include "TCPlayerController.h"
#include "TCPlayerState.h"
#include "TCGameState.h"




void ATCPlayerController::Server_AttackSurvivors_Implementation(ATCPlayerState* TCPlayerState)
{
	ATCGameState* GameState = Cast<ATCGameState>(GetWorld()->GetGameState());

	if (GameState && TCPlayerState)
	{
		GameState->AttackSurvivors(TCPlayerState->Followers, TCPlayerState);
	}
}

bool ATCPlayerController::Server_AttackSurvivors_Validate(ATCPlayerState* TCPlayerState)
{
	return true;
}

void ATCPlayerController::Server_RecruitFollower_Implementation(ATCPlayerState* TCPlayerState)
{
	ATCGameState* GameState = Cast<ATCGameState>(GetWorld()->GetGameState());

	if (GameState && TCPlayerState)
	{
		if (GameState->Survivors > 0 && TCPlayerState->ActionPoints > 0)
		{
			int32 Recruited = FMath::RandRange(1, TCPlayerState->Followers / 5);
			GameState->KillSurvivors(Recruited);
			TCPlayerState->ConsumeActionPoint();
			TCPlayerState->AddFollowers(Recruited);

			if (Recruited > 1)
			{
				GameState->IncreaseHeat();
			}
		}
	}
}

bool ATCPlayerController::Server_RecruitFollower_Validate(ATCPlayerState* TCPlayerState)
{
	return true;
}
