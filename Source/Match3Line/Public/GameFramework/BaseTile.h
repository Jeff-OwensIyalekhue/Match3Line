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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTileDestroyedDelegate, int, DestroyedTileID);

UCLASS()
class MATCH3LINE_API ABaseTile : public AActor
{
	GENERATED_BODY()

protected:
	// Mesh that represents a tile visually
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* TileMesh;

	UPROPERTY()
	UMaterialInstanceDynamic* TileTypeMaterial;

	bool bIsSelected;

	int ID;

private:
	// Type of the tile
	ETileType TileType;
	
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

	UFUNCTION()
	void HandleOnSelectionEnded(bool bIsValidSelection);

	virtual void Destroyed() override;

	FOnTileDestroyedDelegate OnTileDestroyed;
};
