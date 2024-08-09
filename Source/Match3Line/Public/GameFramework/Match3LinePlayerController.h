// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Match3LinePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MATCH3LINE_API AMatch3LinePlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputMappingContext* InputMappingContext;


protected:

	virtual void BeginPlay() override;

};
