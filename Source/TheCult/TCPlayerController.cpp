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

void ATCPlayerController::Server_RecruitFollower_Implementation(ATCPlayerState* TCPlayerState)
{
	ATCGameState* GameState = Cast<ATCGameState>(GetWorld()->GetGameState());

	if (GameState && TCPlayerState)
	{
		if (GameState->Survivors > 0 && TCPlayerState->ConsumeActionPoints(GameState->RecruitPrice))
		{
			int32 Recruited = FMath::RandRange(1, TCPlayerState->Followers / 5);
			GameState->KillSurvivors(Recruited);
			TCPlayerState->AddFollowers(Recruited);

			if (Recruited > 1)
			{
				GameState->IncreaseHeat();
			}
		}
	}
}

void ATCPlayerController::Server_SetLockdown_Implementation(bool bIsLockdown)
{
	SetLockdown(bIsLockdown);
}



void ATCPlayerController::SetLockdown(bool bIsLockdown)
{
	if (HasAuthority())
	{
			ATCPlayerState* TCPlayerState = Cast<ATCPlayerState>(PlayerState);
			auto TCGameState = Cast<ATCGameState>(GetWorld()->GetGameState());
			if (TCPlayerState)
			{
				if (TCPlayerState->ConsumeActionPoints(TCGameState->LockdownPrice))
				{
					TCPlayerState->bIsLockdown = bIsLockdown;
				}
			}
	}
	else if (IsLocalController())
	{
		Server_SetLockdown(bIsLockdown);
	}
}




// Validation
bool ATCPlayerController::Server_AttackSurvivors_Validate(ATCPlayerState* TCPlayerState)
{
	return true;
}

bool ATCPlayerController::Server_RecruitFollower_Validate(ATCPlayerState* TCPlayerState)
{
	return true;
}

bool ATCPlayerController::Server_SetLockdown_Validate(bool bIsLockdown)
{
	return true;
}