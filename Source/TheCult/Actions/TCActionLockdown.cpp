// Fill out your copyright notice in the Description page of Project Settings.

#include "TCActionLockdown.h"
#include "TCPlayerState.h"
#include "TCPlayerController.h"
#include "Camp.h"




void UTCActionLockdown::ActionLogic()
{
	ATCPlayerController* TCPlayerController = Cast<ATCPlayerController>(GetOwner());

	if (TCPlayerController && TCPlayerController->IsLocalController())
	{
		ATCPlayerState* TCPlayerState = Cast<ATCPlayerState>(TCPlayerController->PlayerState);

		if (TCPlayerState)
		{
			if (CanActivate(TCPlayerState->ActionPoints))
			{
				TCPlayerState->GetCamp()->ToggleLockdown();
				GetPlayerState()->ConsumeActionPoints(Cost);

				if (!TCPlayerController->HasAuthority())
				{
					Server_ActionLogic(TCPlayerState);
				}
			}
		}
	}
}

void UTCActionLockdown::Server_ActionLogic_Implementation(ATCPlayerState* TCPlayerState)
{
	if (TCPlayerState)
	{
		if (CanActivate(TCPlayerState->ActionPoints))
		{
			TCPlayerState->GetCamp()->ToggleLockdown();
			GetPlayerState()->ConsumeActionPoints(Cost);
		}
	}
}

bool UTCActionLockdown::Server_ActionLogic_Validate(ATCPlayerState* TCPlayerState)
{
	return true;
}
