// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGrid.generated.h"

class ABaseTile;

UCLASS()
class MATCH3LINE_API ABaseGrid : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GridLayout")
	int GridWidth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GridLayout")
	int GridHeight;

	// Size a tile in the grid occupies
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GridLayout")
	float HexSize; 

	// Reference to the possible positions of the grid
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GridLayout")
	TArray<FVector> GridPositionsArray;	

	// Reference to the tiles of the grid
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GridLayout")
	TArray<ABaseTile*> TileArray;	
	
	// Reference to the tile class to use to create the grid
	UPROPERTY(EditAnywhere, Category = "Tiles")
	TSubclassOf<ABaseTile> Tile; 
	
public:	
	// Sets default values for this actor's properties
	ABaseGrid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Function to generate the Grid
	void GenerateGrid();


	// Function to handle the destruction of tile
	UFUNCTION()
	void OnTileDestroyed(int DestroyedTileID);

};
