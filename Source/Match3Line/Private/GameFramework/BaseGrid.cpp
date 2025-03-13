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
				TileArray[MappedID]->SetID(MappedID);
				TileArray[MappedID]->SetPosition(x, y);
				//TileArray[MappedID]->OnTileDestroyed.AddDynamic(this, &ABaseGrid::OnTileDestroyed);
			}
		}
	}

}

void ABaseGrid::OnTileDestroyed(int DestroyedTileID)
{
	// 
	/*int ReplacingTileID = DestroyedTileID - GridWidth;
	UE_LOG(LogTemp, Warning, TEXT("Tile %i drops to %i"), ReplacingTileID, DestroyedTileID);


	if (ReplacingTileID > 0) 
	{
		if (TileArray[ReplacingTileID])
		{
			TileArray[ReplacingTileID]->SetActorLocation(GridPositionsArray[DestroyedTileID]);
			TileArray[DestroyedTileID]->Destroy();
			TileArray[DestroyedTileID] = TileArray[ReplacingTileID];
		}
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("Create new tile for %i"), DestroyedTileID);
		TileArray[DestroyedTileID]->Destroy();
		TileArray[DestroyedTileID] = GetWorld()->SpawnActor<ABaseTile>(Tile, GridPositionsArray[DestroyedTileID], FRotator::ZeroRotator);
	}*/
	if (!TileArray.IsValidIndex(DestroyedTileID))
	{
		return;
	}

	// Get the destroyed tile and its grid coordinates
	ABaseTile* DestroyedTile = TileArray[DestroyedTileID];
	int Column = DestroyedTile->xPosition;
	int Row = DestroyedTile->yPosition;

	// Remove the destroyed tile from the grid
	TileArray[DestroyedTileID] = nullptr;

	// Shift tiles downward (tiles above drop down)
	// Assuming row 0 is the top row, iterate from the destroyed row down to 1.
	for (int y = Row; y > 0; y--)
	{
		int currentIndex = y * GridWidth + Column;
		int aboveIndex = (y - 1) * GridWidth + Column;

		// Move the tile from above to the current row
		if (TileArray[aboveIndex])
		{
			TileArray[currentIndex] = TileArray[aboveIndex];
			TileArray[currentIndex]->SetPosition(Column, y);
			TileArray[aboveIndex] = nullptr; // Clear the original spot
		}
	}

	// Spawn a new tile at the top (row 0)
	int topIndex = Column;  // since row 0 * GridWidth + Column = Column
	FVector SpawnLocation = GridPositionsArray[topIndex];
	ABaseTile* NewTile = GetWorld()->SpawnActor<ABaseTile>(Tile, SpawnLocation, FRotator::ZeroRotator);
	if (NewTile)
	{
		NewTile->SetPosition(Column, 0);
		TileArray[topIndex] = NewTile;
	}
}

