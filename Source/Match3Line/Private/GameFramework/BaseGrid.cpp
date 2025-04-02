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
				TileArray[MappedID]->Id = MappedID;
			}
		}
	}

}

bool ABaseGrid::IsDirectNeighbor(int BaseTileId, int OtherTileId)
{
	// Calculate grid coordinates from Ids:
	int BaseX = BaseTileId % GridWidth;      // x corresponds to inner-loop index
	int BaseY = BaseTileId / GridWidth;
	int OtherX = OtherTileId % GridWidth;
	int OtherY = OtherTileId / GridWidth;

	// Define neighbor offsets based on an odd-row (x) offset hex grid:
	TArray<FIntPoint> NeighborOffsets;
	if (BaseX % 2 == 0)
	{
		// Even row offsets
		NeighborOffsets = {
			FIntPoint(0, -1),  // Left
			FIntPoint(0, +1),  // Right
			FIntPoint(-1, -1),  // Upper left
			FIntPoint(-1,  0),  // Upper right
			FIntPoint(+1, -1),  // Lower left
			FIntPoint(+1,  0)   // Lower right
		};
	}
	else
	{
		// Odd row offsets
		NeighborOffsets = {
			FIntPoint(0, -1),  // Left
			FIntPoint(0, +1),  // Right
			FIntPoint(-1,  0),  // Upper left
			FIntPoint(-1, +1),  // Upper right
			FIntPoint(+1,  0),  // Lower left
			FIntPoint(+1, +1)   // Lower right
		};
	}

	// Check if OtherTile's coordinate is one of the neighbor positions:
	for (const FIntPoint& Offset : NeighborOffsets)
	{
		int NeighborX = BaseX + Offset.X;
		int NeighborY = BaseY + Offset.Y;

		// Optionally, check that NeighborX and NeighborY are within grid bounds:
		if (NeighborX < 0 || NeighborX >= GridWidth ||
			NeighborY < 0 || NeighborY >= GridHeight)
		{
			continue;
		}

		if (NeighborX == OtherX && NeighborY == OtherY)
		{
			return true;
		}
	}

	return false;
}

void ABaseGrid::DestroySelectedTiles(const TArray<int>& TileIds)
{
	for (int TileId : TileIds)
	{
		DestroyTile(TileId);
	}
}

void ABaseGrid::DestroyTile(int Id)
{
	if (!TileArray.IsValidIndex(Id) || !TileArray[Id])
	{
		return;  // No tile to destroy here.
	}

	// Explicitly destroy the tile actor.
	ABaseTile* TileToDestroy = TileArray[Id];
	TileToDestroy->Destroy();
	TileArray[Id] = nullptr;

	// Shift tiles in the column down.
	ShiftColumnDown(Id);
}

void ABaseGrid::ShiftColumnDown(int Id)
{
	if (TileArray.IsValidIndex(Id - GridWidth))
	{
		TileArray[Id] = TileArray[Id - GridWidth];
		TileArray[Id]->Id = Id;

		// Update the tile's position to its new grid location.
		TileArray[Id]->SetActorLocation(GridPositionsArray[Id]);
		ShiftColumnDown(Id - GridWidth);
	}
	else
	{
		SpawnTileAtTop(Id);
	}
}

void ABaseGrid::SpawnTileAtTop(int Id)
{
	double Row = Id % GridWidth;

	// Spawn a new tile at row 0 for the specified column.
	FVector SpawnLocation = GridPositionsArray[Row];
	
	ABaseTile* NewTile = GetWorld()->SpawnActor<ABaseTile>(Tile, SpawnLocation, FRotator::ZeroRotator);
	if (NewTile)
	{
		NewTile->Id = Id;
		TileArray[Id] = NewTile;
	}
}
