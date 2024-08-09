// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGrid.generated.h"

//class ABaseTile;

UCLASS()
class MATCH3LINE_API ABaseGrid : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GridLayout")
	int GridWidth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GridLayout")
	int GridHeight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GridLayout")
	float HexSize;

	// Reference to the tile class to use to create the grid
	UPROPERTY(EditAnywhere, Category = "Tiles")
	TSubclassOf<class ABaseTile> Tile;
	
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
	void GenerateGrid();

};
