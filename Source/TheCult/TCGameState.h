// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "TCGameState.generated.h"

/**
 * 
 */
UCLASS()
class THECULT_API ATCGameState : public AGameState
{
	GENERATED_BODY()

public:

	ATCGameState();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString CurrentVersion = "0.0.7";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated)
	int32 Survivors = 100000;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated)
	float Heat = 0.0f;

	UFUNCTION(BlueprintCallable)
	void KillSurvivors(int32 KilledSurvivors);


	
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Server: Kill survivors based on strength
	UFUNCTION(BlueprintCallable)
	void AttackSurvivors(int32 Strength, ATCPlayerState* PlayerState);

	// Increase heat
	// Raid players
	// Arrest players
	// Block 


		// Heat
		// Check on another timer
	UFUNCTION()
	void IncreaseHeat();

	UFUNCTION()
	void DecreaseHeat();

	UFUNCTION()
	void RaidOnCultists();


	UFUNCTION()
	void IncreasePopulation();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Replicated)
	TArray<FString> LastNews;

	UFUNCTION()
	void AddNews(FString NewsToAdd);

	
};
