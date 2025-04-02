// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/BaseTile.h"
#include "GameFramework/Match3LineCharacter.h"
//#include "Components/TextRenderComponent.h"

// Sets default values
ABaseTile::ABaseTile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tile Mesh"));
	RootComponent = TileMesh;
	//TextRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text Render"));

}

// Called when the game starts or when spawned
void ABaseTile::BeginPlay()
{
	Super::BeginPlay();

}

void ABaseTile::OnConstruction(const FTransform& Transform)
{
	// Call the base function
	Super::OnConstruction(Transform);

	bIsSelected = false;

	TileType = (ETileType)FMath::RandRange(0, 3);

	UMaterialInterface* MaterialToEdit = TileMesh->GetMaterial(0);
	TileTypeMaterial = UMaterialInstanceDynamic::Create(MaterialToEdit, this);

	FLinearColor TileColor;

	switch (TileType)
	{
	case ETileType::Red:
		TileColor = FLinearColor::Red;
		break;
	case ETileType::Green:
		TileColor = FLinearColor::Green;
		break;
	case ETileType::Blue:
		TileColor = FLinearColor::Blue;
		break;
	case ETileType::Yellow:
		TileColor = FLinearColor::Yellow;
		break;
	default:
		break;
	}

	TileTypeMaterial->SetVectorParameterValue(FName("Tint"), TileColor);

	TileMesh->SetMaterial(0, TileTypeMaterial);
}

// Called every frame
void ABaseTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ABaseTile::SelectTile(AMatch3LineCharacter* Selector)
{
	if (!bIsSelected)
	{
		bIsSelected = true;
		TileTypeMaterial->SetVectorParameterValue(FName("Tint"), FLinearColor::White);
		TileMesh->SetMaterial(0, TileTypeMaterial);

		// ToDo bind to grid not tiles?
		//Selector->OnSelectionEnded.AddDynamic(this, &ABaseTile::HandleOnSelectionEnded);

		return true;
	}

	return false;
}

void ABaseTile::DeselesctTile(AMatch3LineCharacter* Selector)
{

	bIsSelected = false;

#pragma region return color scheme

	FLinearColor TileColor;

	switch (TileType)
	{
	case ETileType::Red:
		TileColor = FLinearColor::Red;
		break;
	case ETileType::Green:
		TileColor = FLinearColor::Green;
		break;
	case ETileType::Blue:
		TileColor = FLinearColor::Blue;
		break;
	case ETileType::Yellow:
		TileColor = FLinearColor::Yellow;
		break;
	default:
		break;
	}

	TileTypeMaterial->SetVectorParameterValue(FName("Tint"), TileColor);

	TileMesh->SetMaterial(0, TileTypeMaterial);

#pragma endregion

	//Selector->OnSelectionEnded.RemoveDynamic(this, &ABaseTile::HandleOnSelectionEnded);
}