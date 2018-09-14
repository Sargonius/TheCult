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
	int32 Followers = 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated)
	int32 ActionPoints = 3;	

	UFUNCTION(BlueprintCallable)
	void AddActionPoint();

	UFUNCTION(BlueprintCallable)
	void ConsumeActionPoint();

	UFUNCTION(BlueprintCallable)
	void AddFollower();

	UFUNCTION(BlueprintCallable)
	void KillFollower();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Adepts
	// Power
	// Money
	// Weapons

	// Is Cult Cell alive
	// Level (increases max AP and allows to do more per action
	
};
