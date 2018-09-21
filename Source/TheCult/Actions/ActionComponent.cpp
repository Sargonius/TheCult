// Fill out your copyright notice in the Description page of Project Settings.

#include "ActionComponent.h"


// Sets default values for this component's properties
UActionComponent::UActionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UActionComponent::BeginPlay()
{
	Super::BeginPlay();	
}

bool UActionComponent::CanActivate(int32 ActionPoints)
{
	if (ActionPoints >= Cost && !bIsOnCooldown)
	{
		return true;
	}

	return false;
}

void UActionComponent::ActivateAction()
{
	OnActivateAction();
	ReceiveOnActivate();
	
	if (CooldownTime > 0)
	{
		GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &UActionComponent::ResetCooldown, CooldownTime, false);
		bIsOnCooldown = true;
	}
}

void UActionComponent::OnActivateAction()
{

}

void UActionComponent::ResetCooldown()
{
	bIsOnCooldown = false;
}
