// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Match3LineCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelectionEndedDelegate, bool, bIsValidSelection);

UCLASS()
class MATCH3LINE_API AMatch3LineCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	// Camera component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FixedCamera;

	TArray<class BaseTile*> SelectedTiles;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* StartSelectionAction;
	

public:
	// Sets default values for this character's properties
	AMatch3LineCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Function bound to the event when the left mouse button is tiggered, calls GetTileUnderCursor()
	void StartSelection();

	// Functionbound to the event when the left mouse button is released, 
	void EndSelection();

	FOnSelectionEndedDelegate OnSelectionEnded;

	// Function to get the tile the mouse cursor points to
	class ABaseTile* GetTileUnderCursor();
};
