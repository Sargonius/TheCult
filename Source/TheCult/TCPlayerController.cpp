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
			GameState->KillSurvivors(1);
			TCPlayerState->ConsumeActionPoint();
			TCPlayerState->AddFollower();
		}
	}
}

bool ATCPlayerController::Server_RecruitFollower_Validate(ATCPlayerState* TCPlayerState)
{
	return true;
}
