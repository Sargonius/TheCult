// Fill out your copyright notice in the Description page of Project Settings.

#include "TCPlayerState.h"
#include "UnrealNetwork.h"




ATCPlayerState::ATCPlayerState()
{
	bReplicates = true;
}

void ATCPlayerState::AddActionPoint()
{
	ActionPoints++;
	UE_LOG(LogTemp, Warning, TEXT("Got another action point."));
}

void ATCPlayerState::ConsumeActionPoint()
{
	ActionPoints--;
	UE_LOG(LogTemp, Warning, TEXT("%s: Action point spent."), *GetPlayerName());
}

void ATCPlayerState::AddFollower()
{
	Followers++;
	UE_LOG(LogTemp, Warning, TEXT("%s: New follower joins your cell."), *GetPlayerName());
}

void ATCPlayerState::KillFollower()
{
	if (Followers > 0)
	{
		Followers--;
		UE_LOG(LogTemp, Warning, TEXT("%s: A follower died in action."), *GetPlayerName());
	}
}

void ATCPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATCPlayerState, Followers);
	DOREPLIFETIME(ATCPlayerState, ActionPoints);
}
