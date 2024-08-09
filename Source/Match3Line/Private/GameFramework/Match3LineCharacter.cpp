// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/Match3LineCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/BaseTile.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"

// Sets default values
AMatch3LineCharacter::AMatch3LineCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Disable character movement
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	// Disable physics on the capsule component (the root component)
	GetCapsuleComponent()->SetSimulatePhysics(false);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Disable gravity for the character
	GetCharacterMovement()->GravityScale = 0.0f;

	// Optional: Disable character movement component completely
	GetCharacterMovement()->DisableMovement();

	// Set up the camera component
	FixedCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FixedCamera"));
	FixedCamera->SetupAttachment(RootComponent);

	FixedCamera->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
}

// Called when the game starts or when spawned
void AMatch3LineCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMatch3LineCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMatch3LineCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Triggered, this, &AMatch3LineCharacter::Interact);
	}
}

void AMatch3LineCharacter::Interact()
{
	AActor* TileUnderCursor = GetTileUnderCursor();
	if (TileUnderCursor)
	{
		// Implement your interaction logic here
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Interacted with: %s"), *TileUnderCursor->GetName()));
		// You can call any function or modify any property of the actor here
	}
}

AActor* AMatch3LineCharacter::GetTileUnderCursor()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		FVector WorldLocation, WorldDirection;
		if (PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
		{
			FVector Start = WorldLocation;
			FVector End = Start + (WorldDirection * 10000.0f); // Trace 10,000 units into the world

			FHitResult HitResult;
			GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);

			if ((HitResult.GetActor()))
			{
				// Optionally draw a debug line in the editor to visualize the trace
				DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.0f, 0, 1.0f);
				return (HitResult.GetActor());
			}
		}
	}

	return nullptr;
}

