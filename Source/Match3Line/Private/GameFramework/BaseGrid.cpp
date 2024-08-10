// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/BaseGrid.h"
#include "GameFramework/BaseTile.h"

// Sets default values
ABaseGrid::ABaseGrid()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set the deafult values for the grid layout
	GridWidth = 7;
	GridHeight = 6;
	HexSize = 100.0f;
	TileArray.SetNum(GridWidth * GridHeight, false);
	GridPositionsArray.SetNum(GridWidth * GridHeight, false);

}

// Called when the game starts or when spawned
void ABaseGrid::BeginPlay()
{
	Super::BeginPlay();

	GenerateGrid();
}

// Called every frame
void ABaseGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseGrid::GenerateGrid()
{
	const float HexWidth = HexSize;
	const float HexHeight = (sqrt(3) / 2) * HexWidth;

	for (int y = 0; y < GridHeight; y++)
	{
		for (int x = 0; x < GridWidth; x++)
		{
			// Spawn Tile on with regard of hex grid offset
			float XOffset = y * HexWidth;
			float YOffset = x * HexHeight;

			if (x % 2 != 0)
			{
				XOffset += HexWidth / 2;
			}

			FVector HexLocation(-XOffset, YOffset, 0.0f);

			// Spawn tile and add tile to array
			int MappedID = x + (y * GridWidth);

			GridPositionsArray[MappedID] = HexLocation;
			TileArray[MappedID] = GetWorld()->SpawnActor<ABaseTile>(Tile, HexLocation, FRotator::ZeroRotator);

			if (TileArray[MappedID])
			{
				TileArray[MappedID]->OnTileDestroyed.AddDynamic(this, &ABaseGrid::OnTileDestroyed);
			}
		}
	}

}

void ABaseGrid::OnTileDestroyed(int DestroyedTileID)
{
	// 
	UE_LOG(LogTemp, Warning, TEXT("Tile gone %i"), DestroyedTileID);
	int ReplacingTileID = DestroyedTileID - GridWidth;
	UE_LOG(LogTemp, Warning, TEXT("Tile drops %i"), ReplacingTileID);


	if (ReplacingTileID > 0) 
	{
		if (TileArray[ReplacingTileID])
		{
			TileArray[ReplacingTileID]->SetActorLocation(GridPositionsArray[DestroyedTileID]);
			TileArray[DestroyedTileID] = TileArray[ReplacingTileID];
			TileArray[ReplacingTileID]->Destroy();
		}
	}
	else 
	{
		TileArray[DestroyedTileID] = GetWorld()->SpawnActor<ABaseTile>(Tile, GridPositionsArray[DestroyedTileID], FRotator::ZeroRotator);
	}
}

