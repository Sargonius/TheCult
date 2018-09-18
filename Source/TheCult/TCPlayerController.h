// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TCPlayerState.h"
#include "GameFramework/PlayerController.h"
#include "TCPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class THECULT_API ATCPlayerController : public APlayerController
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
	void Server_AttackSurvivors(ATCPlayerState* TCPlayerState);

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
	void Server_RecruitFollower(ATCPlayerState* TCPlayerState);

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
	void Server_SetLockdown(bool bIsLockdown);

	UFUNCTION(BlueprintCallable)
	void SetLockdown(bool bIsLockdown);
	
	
};
