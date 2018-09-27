// Fill out your copyright notice in the Description page of Project Settings.

#include "Camp.h"
#include "UnrealNetwork.h"
#include "TimerManager.h"


// Sets default values
ACamp::ACamp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	bAlwaysRelevant = true;
}

void ACamp::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACamp, Population);
	DOREPLIFETIME(ACamp, PopulationLimit);
	DOREPLIFETIME(ACamp, bIsLockdown);
}

void ACamp::Kill(int32 PopulationToKill)
{
	int32 RealKills = FMath::Clamp(PopulationToKill, 0, Population);

	Population -= RealKills;
}

void ACamp::IncreasePopulation(int32 PopulationToAdd)
{
	int32 RealIncrease = FMath::Clamp(PopulationToAdd, 0, PopulationLimit);

	Population += RealIncrease;
}

void ACamp::ToggleLockdown()
{
	bIsLockdown = !bIsLockdown;
}

// Called when the game starts or when spawned
void ACamp::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void ACamp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

