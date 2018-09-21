// Fill out your copyright notice in the Description page of Project Settings.

#include "TCPlayerController.h"
#include "TCPlayerState.h"
#include "TCGameState.h"
#include "Camp.h"

void ATCPlayerController::Server_RecruitFollower_Implementation(int32 NumberToRecruit)
{
	ATCGameState* GameState = Cast<ATCGameState>(GetWorld()->GetGameState());
	ATCPlayerState* TCPlayerState = Cast<ATCPlayerState>(PlayerState);

	if (GameState && TCPlayerState)
	{
		if (GameState->GetCamp()->Population > 0 && TCPlayerState->ConsumeActionPoints(GameState->RecruitPrice))
		{
			GameState->GetCamp()->Kill(NumberToRecruit);
			TCPlayerState->GetCamp()->IncreasePopulation(NumberToRecruit);
			//TCPlayerState->AddFollowers(NumberToRecruit);

			if (NumberToRecruit > 1)
			{
				GameState->IncreaseHeat();
			}
		}
	}
}

void ATCPlayerController::RecruitFollower()
{
	ATCGameState* GameState = Cast<ATCGameState>(GetWorld()->GetGameState());
	ATCPlayerState* TCPlayerState = Cast<ATCPlayerState>(PlayerState);

	if (GameState && TCPlayerState)
	{
		if (GameState->GetCamp()->Population > 0 && TCPlayerState->ConsumeActionPoints(GameState->RecruitPrice))
		{
			int32 Recruited = FMath::RandRange(1, TCPlayerState->GetCamp()->Population / 5);
			GameState->GetCamp()->Kill(Recruited);
			TCPlayerState->GetCamp()->IncreasePopulation(Recruited);

			if (IsLocalController())
			{
				Server_RecruitFollower(Recruited);
			}
		}
	}
}

void ATCPlayerController::AttackSurvivors()
{
	ATCGameState* GameState = Cast<ATCGameState>(GetWorld()->GetGameState());
	ATCPlayerState* TCPlayerState = Cast<ATCPlayerState>(PlayerState);

	if (GameState && TCPlayerState)
	{
		GameState->AttackSurvivors(TCPlayerState->GetCamp()->Population, TCPlayerState);
	}
}

void ATCPlayerController::Server_AttackSurvivors_Implementation(int32  NumberToKill)
{
	ATCGameState* GameState = Cast<ATCGameState>(GetWorld()->GetGameState());

	if (GameState)
	{
		//GameState->AttackSurvivors(NumberToKill);
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
					TCPlayerState->GetCamp()->ToggleLockdown();
				}
			}
	}
	else if (IsLocalController())
	{
		Server_SetLockdown(bIsLockdown);
	}
}




// Validation
bool ATCPlayerController::Server_AttackSurvivors_Validate(int32 AmountToKill)
{
	return true;
}

bool ATCPlayerController::Server_RecruitFollower_Validate(int32 NumberToRecruit)
{
	return true;
}

bool ATCPlayerController::Server_SetLockdown_Validate(bool bIsLockdown)
{
	return true;
}