// Fill out your copyright notice in the Description page of Project Settings.

#include "TCActionRecruit.h"
#include "TCPlayerState.h"
#include "TCGameState.h"
#include "TCPlayerController.h"
#include "Camp.h"
#include "Engine/World.h"
#include "TimerManager.h"


void UTCActionRecruit::ActionLogic()
{
	ATCPlayerController* TCPlayerController = Cast<ATCPlayerController>(GetOwner());

	if (TCPlayerController && TCPlayerController->IsLocalController())
	{
		ATCGameState* GameState = Cast<ATCGameState>(GetWorld()->GetGameState());
		ATCPlayerState* TCPlayerState = Cast<ATCPlayerState>(TCPlayerController->PlayerState);

		if (GameState && TCPlayerState)
		{
			if (GameState->GetCamp()->Population > 0 && CanActivate(TCPlayerState->ActionPoints))
			{
				int32 Recruited = FMath::RandRange(1, 1 + FMath::TruncToInt(TCPlayerState->GetCamp()->Population / 100.0f * MaxRecruitedPercent));
				GameState->GetCamp()->Kill(Recruited);
				TCPlayerState->GetCamp()->IncreasePopulation(Recruited);
				GetPlayerState()->ConsumeActionPoints(Cost);

				if (Recruited > 1)
				{
					GameState->IncreaseHeat();
				}

				if (!TCPlayerController->HasAuthority())
				{
					Server_ActionLogic(TCPlayerState, Recruited);
				}
			}
		}
	}
}

void UTCActionRecruit::Server_ActionLogic_Implementation(ATCPlayerState* TCPlayerState, int32 Recruited)
{
	ATCGameState* GameState = Cast<ATCGameState>(GetWorld()->GetGameState());
	if (GameState && TCPlayerState)
	{
		if (GameState->GetCamp()->Population > 0 && CanActivate(TCPlayerState->ActionPoints))
		{
			GameState->GetCamp()->Kill(Recruited);
			TCPlayerState->GetCamp()->IncreasePopulation(Recruited);
			GetPlayerState()->ConsumeActionPoints(Cost);

			if (Recruited > 1)
			{
				GameState->IncreaseHeat();
			}
		}
	}
}

bool UTCActionRecruit::Server_ActionLogic_Validate(ATCPlayerState* TCPlayerState, int32 Recruited)
{
	if (Recruited > TCPlayerState->GetCamp()->Population)
	{
		return false;
	}

	return true;
}