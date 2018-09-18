// Fill out your copyright notice in the Description page of Project Settings.

#include "TCPlayerState.h"
#include "UnrealNetwork.h"




ATCPlayerState::ATCPlayerState()
{
	bReplicates = true;
}

void ATCPlayerState::AddActionPoints(int32 ActionPointsToAdd)
{
	ActionPoints += ActionPointsToAdd;
	UE_LOG(LogTemp, Warning, TEXT("Got another action point."));
}


bool ATCPlayerState::ConsumeActionPoints(int32 ActionPointsToConsume)
{
	if (ActionPoints >= ActionPointsToConsume)
	{
		ActionPoints -= ActionPointsToConsume;
		UE_LOG(LogTemp, Warning, TEXT("%s: Action points used: %d"), *GetPlayerName(), ActionPointsToConsume);
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: Not enough Action Points!"), *GetPlayerName(), ActionPointsToConsume);
		return false;
	}
}

void ATCPlayerState::AddFollowers(int32 Amount)
{
	Followers += Amount;
	UE_LOG(LogTemp, Warning, TEXT("%s: New followers joins your cell: %d"), *GetPlayerName(), Amount);
}

void ATCPlayerState::KillFollowers(int32 Amount)
{
	if (Followers > 0)
	{
		Amount = FMath::Clamp(Amount, 0, Followers);
		Followers -= Amount;
		UE_LOG(LogTemp, Warning, TEXT("%s: Followers died in action: %d"), *GetPlayerName(), Amount);
	}
}

void ATCPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATCPlayerState, Followers);
	DOREPLIFETIME(ATCPlayerState, ActionPoints);
	DOREPLIFETIME(ATCPlayerState, bIsLockdown);
}
