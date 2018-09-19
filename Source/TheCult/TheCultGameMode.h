// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TheCultGameMode.generated.h"

/**
 * 
 */
UCLASS()
class THECULT_API ATCGameMode : public AGameMode
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;

public:
	// AP Logic
	FTimerHandle UpdateActionPointsTimer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MaxAP = 3;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float APUpdateRate = 5.0f;

	UFUNCTION()
	void GiveActionPoints();	

	// Heat Management
	FTimerHandle UpdateHeatTimer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float HeatUpdateRate = 5.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float HeatThresholdBeforeRetaliation = 0.5f;

	UFUNCTION()
	void UpdateHeat();

	FTimerHandle UpdatePopulationTimer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float PopulationUpdateRate = 20.0f;

	UFUNCTION()
	void UpdatePopulation();

	FTimerHandle UpdateDayTimer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float DayUpdateTimer = 10.0f;

	UFUNCTION()
	void UpdateDay();

	UFUNCTION()
		void CalculateEndGameStats();
	
};
