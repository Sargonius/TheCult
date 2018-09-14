// Fill out your copyright notice in the Description page of Project Settings.

#include "TCGameState.h"
#include "TCPlayerState.h"
#include "UnrealNetwork.h"

ATCGameState::ATCGameState()
{
	bReplicates = true;
}

void ATCGameState::KillSurvivors(int32 KilledSurvivors)
{
	Survivors -= KilledSurvivors;
	UE_LOG(LogTemp, Warning, TEXT("Killed %d survivors!"), KilledSurvivors);
}

void ATCGameState::BeginPlay()
{
	Super::BeginPlay();


}

void ATCGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATCGameState, Survivors);
	DOREPLIFETIME(ATCGameState, Heat);
}

void ATCGameState::AttackSurvivors(int32 Strength, ATCPlayerState* PlayerState)
{
	if (!HasAuthority())
	{
		return;
	}

	if (PlayerState && PlayerState->ActionPoints > 0)
	{
		int32 KilledSurvivors = Strength;
		FMath::Clamp(KilledSurvivors, 0, Survivors);

		KillSurvivors(KilledSurvivors);

		IncreaseHeat();

		PlayerState->ConsumeActionPoint();
	}
}

void ATCGameState::IncreaseHeat()
{
	Heat += FMath::RandRange(0.01f, 0.1f);
	FMath::Clamp(Heat, 0.0f, 1.0f);
}

void ATCGameState::DecreaseHeat()
{
	Heat -= FMath::RandRange(0.01f, 0.1f);
	FMath::Clamp(Heat, 0.0f, 1.0f);
}

// Action - has price, handles action logic, checks AP