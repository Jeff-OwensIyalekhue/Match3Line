// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/Match3LinePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

void AMatch3LinePlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;

	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}
