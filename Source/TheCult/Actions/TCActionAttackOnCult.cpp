// Fill out your copyright notice in the Description page of Project Settings.

#include "TCActionAttackOnCult.h"
#include "TCGameState.h"
#include "TCPlayerState.h"
#include "Camp.h"
#include "Engine/World.h"

void UTCActionAttackOnCult::ActionLogic()
{
	int32 TotalCasualities = 0;

	ATCGameState* TCGameState = Cast<ATCGameState>(GetWorld()->GetGameState());

	if (TCGameState)
	{
		for (auto PlayerState : TCGameState->PlayerArray)
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

		TCGameState->AddNews(FString("Survivors raided a cult hideout! Killed: " + FString::FromInt(TotalCasualities)));
	}
}
