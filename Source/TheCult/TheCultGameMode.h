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

	UFUNCTION()
	void GiveActionPoints();	

	// Heat Management
	FTimerHandle UpdateHeatTimer;

	UFUNCTION()
	void UpdateHeat();
	
};
