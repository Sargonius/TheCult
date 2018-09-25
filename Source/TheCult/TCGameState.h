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
	FString CurrentVersion = "0.3.1";

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Replicated)
	class ACamp* Camp;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	ACamp* GetCamp();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated)
	float Heat = 0.0f;

	UFUNCTION(BlueprintCallable)
	void KillSurvivors(int32 KilledSurvivors);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated)
	int32 CurrentDay = 1;


	
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Server: Kill survivors based on strength
	UFUNCTION(BlueprintCallable)
	void AttackSurvivors(int32 Strength, ATCPlayerState* PlayerState);

	UFUNCTION()
	void IncreasePopulation();

	UFUNCTION()
	void IncreaseHeat();

	UFUNCTION()
	void DecreaseHeat();

	UFUNCTION()
	void RaidOnCultists();

	// Increase heat
// Raid players
// Arrest players
// Block 


	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Replicated)
	TArray<FString> LastNews;

	UFUNCTION()
	void AddNews(FString NewsToAdd);


	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 LockdownPrice = 3;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 RecruitPrice = 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 AttackPrice = 1;

	
};
