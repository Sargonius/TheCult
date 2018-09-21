// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TCPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class THECULT_API ATCPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	ATCPlayerState();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated)
	class ACamp* Camp;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	ACamp* GetCamp();

	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated)
	//bool bIsLockdown = false;

	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated)
	//int32 Followers = 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated)
	int32 ActionPoints = 3;	

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated)
	int32 MaxActionPoints = 3;

	UFUNCTION(BlueprintCallable)
	void AddActionPoints(int32 ActionPointsToAdd);

	UFUNCTION(BlueprintCallable)
	bool ConsumeActionPoints(int32 ActionPointsToConsume);

	UFUNCTION(BlueprintCallable)
	void AddFollowers(int32 Amount);

	UFUNCTION(BlueprintCallable)
	void KillFollowers(int32 Amount);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Adepts
	// Power
	// Money
	// Weapons

	// Is Cult Cell alive
	// Level (increases max AP and allows to do more per action
	
};
