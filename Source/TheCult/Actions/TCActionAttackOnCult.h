// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ActionComponent.h"
#include "TCActionAttackOnCult.generated.h"

/**
 * 
 */
UCLASS()
class THECULT_API UTCActionAttackOnCult : public UActionComponent
{
	GENERATED_BODY()
	
	void ActionLogic() override;
	
};
