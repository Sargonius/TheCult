// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camp.generated.h"

UCLASS()
class THECULT_API ACamp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACamp();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated)
	int32 Population = 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated)
	int32 PopulationLimit = 100000;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated)
	bool bIsLockdown = false;

	UFUNCTION(BlueprintCallable)
	void Kill(int32 PopulationToKill);

	UFUNCTION(BlueprintCallable)
	void IncreasePopulation(int32 PopulationToAdd);

	UFUNCTION(BlueprintCallable)
	void ToggleLockdown();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	
	
};
