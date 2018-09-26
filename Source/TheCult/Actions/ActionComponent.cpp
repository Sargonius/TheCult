// Fill out your copyright notice in the Description page of Project Settings.

#include "ActionComponent.h"
#include "TCPlayerState.h"
#include "TCPlayerController.h"

UActionComponent::UActionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

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
	if (GetPlayerState() && CanActivate(GetPlayerState()->ActionPoints))
	{
		ActionLogic();
		ReceiveOnActivate();

		if (CooldownTime > 0)
		{
			GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &UActionComponent::ResetCooldown, CooldownTime, false);
			bIsOnCooldown = true;
		}
	}
}

void UActionComponent::ActivateActionWithoutChecks()
{
	ActionLogic();
	ReceiveOnActivate();

	if (CooldownTime > 0)
	{
		GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &UActionComponent::ResetCooldown, CooldownTime, false);
		bIsOnCooldown = true;
	}
}

void UActionComponent::ActionLogic()
{

}

void UActionComponent::ResetCooldown()
{
	bIsOnCooldown = false;
}

ATCPlayerState* UActionComponent::GetPlayerState()
{
	auto TCController = Cast<ATCPlayerController>(GetOwner());
	if (TCController)
	{
		auto TCPlayerState = Cast<ATCPlayerState>(TCController->PlayerState);
		if (TCPlayerState)
		{
			return TCPlayerState;
		}
	}

	return nullptr;
}
