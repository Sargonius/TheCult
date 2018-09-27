// Fill out your copyright notice in the Description page of Project Settings.

#include "TCActionAttack.h"
#include "TCPlayerState.h"
#include "TCGameState.h"
#include "TCPlayerController.h"
#include "Camp.h"
#include "Engine/World.h"
#include "TimerManager.h"

void UTCActionAttack::ActionLogic()
{
	ATCPlayerController* TCPlayerController = Cast<ATCPlayerController>(GetOwner());

	if (TCPlayerController && TCPlayerController->IsLocalController())
	{

		ATCGameState* GameState = Cast<ATCGameState>(GetWorld()->GetGameState());
		ATCPlayerState* TCPlayerState = Cast<ATCPlayerState>(TCPlayerController->PlayerState);

		if (GameState && TCPlayerState)
		{
			if (CanActivate(TCPlayerState->ActionPoints))
			{
				int32 KilledSurvivors = FMath::RandRange(1, 1 + FMath::TruncToInt(TCPlayerState->GetCamp()->Population / 100.0f * MaxPossibleAttackDamageInPercents));
				GameState->AddNews(FString("The cult attacks again! Survivors killed: " + FString::FromInt(KilledSurvivors)));
				GameState->Camp->Kill(KilledSurvivors);
				GameState->IncreaseHeat();
				GetPlayerState()->ConsumeActionPoints(Cost);

				if (!TCPlayerController->HasAuthority())
				{
					Server_ActionLogic(TCPlayerState, KilledSurvivors);
				}
			}
		}
	}
}

void UTCActionAttack::Server_ActionLogic_Implementation(ATCPlayerState* TCPlayerState, int32 Killed)
{
	ATCGameState* GameState = Cast<ATCGameState>(GetWorld()->GetGameState());
	if (GameState && TCPlayerState)
	{
		if (CanActivate(TCPlayerState->ActionPoints))
		{
			GameState->AddNews(FString("The cult attacks again! Survivors killed: " + FString::FromInt(Killed)));
			GameState->Camp->Kill(Killed);
			GameState->IncreaseHeat();
			GetPlayerState()->ConsumeActionPoints(Cost);
		}
	}
}

bool UTCActionAttack::Server_ActionLogic_Validate(ATCPlayerState* TCPlayerState, int32 Killed)
{
// 	if (Killed > 1 + FMath::TruncToInt(TCPlayerState->GetCamp()->Population / 100 * MaxPossibleAttackDamageInPercents))
// 	{
// 		return false;
// 	}

	return true;
}

