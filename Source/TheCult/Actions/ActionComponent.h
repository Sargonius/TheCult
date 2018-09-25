// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActionComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THECULT_API UActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UActionComponent();

protected:
	virtual void BeginPlay() override;

public:	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Cost = 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CooldownTime = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsOnCooldown = false;

	FTimerHandle CooldownTimerHandle;

	UFUNCTION(BlueprintCallable)
	bool CanActivate(int32 ActionPoints);

	UFUNCTION(BlueprintCallable)
	void ActivateAction();

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveOnActivate();

	UFUNCTION(BlueprintCallable)
	virtual void ActionLogic();

	UFUNCTION(BlueprintCallable)
	void ResetCooldown();	

	UFUNCTION(BlueprintCallable)
	ATCPlayerState* GetPlayerState();
};
