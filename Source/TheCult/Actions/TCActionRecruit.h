// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ActionComponent.h"
#include "TCActionRecruit.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THECULT_API UTCActionRecruit : public UActionComponent
{
	GENERATED_BODY()

	void ActionLogic() override;	

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
	void Server_ActionLogic(ATCPlayerState* TCPlayerState, int32 Recruited);

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MaxRecruitedPercent = 10.0f;
	
};
