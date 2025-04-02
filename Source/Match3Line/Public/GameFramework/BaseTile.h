// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseTile.generated.h"

UENUM(BlueprintType)
enum class ETileType : uint8
{
	Red,
	Green,
	Blue,
	Yellow
};


UCLASS()
class MATCH3LINE_API ABaseTile : public AActor
{
	GENERATED_BODY()

protected:
	// Mesh that represents a tile visually
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* TileMesh;

	/*UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UTextRenderComponent* TextRender;*/

	UPROPERTY()
	UMaterialInstanceDynamic* TileTypeMaterial;

	bool bIsSelected;


public:
	// Type of the tile
	UPROPERTY(VisibleAnywhere)
	ETileType TileType;

	UPROPERTY(VisibleAnywhere)
	int Id;
	
public:	
	// Sets default values for this actor's properties
	ABaseTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Override the construction to set the tile type 
	virtual void OnConstruction(const FTransform& Transform) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	bool SelectTile(class AMatch3LineCharacter* Selector);

	// Function to deselect a tile for the case this happens during the selection phase -> moving the line backwards the selection
	UFUNCTION()
	void DeselesctTile(class AMatch3LineCharacter* Selector);
};
