// Fill out your copyright notice in the Description page of Project Settings.

#include "ARoad.h"
#include "UObjects/UTile.h"
#include "AStructure.h"
#include "Libraries/UGridLibrary.h"


// Sets default values
ARoad::ARoad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bShouldUpdate = true;
	bIsOneWay = false;
	OneWayDirection = 0;
}
void ARoad::AddEntrance(AStructure* Structure)
{
	if (Structure)
	{
		Entrances.AddUnique(Structure);
	}
}
void ARoad::AddExit(AStructure* Structure)
{
	if (Structure)
	{
		Exits.AddUnique(Structure);
	}
}
bool ARoad::HasEntranceOfClass(TSubclassOf<class AStructure> StructureClass)
{
	for (auto& Structure : Entrances)
	{
		if (Structure && Structure->GetClass() == StructureClass)
		{
			return true;
		}
	}
	return false;
}
void ARoad::UpdatePaths()
{
	if (bShouldUpdate)
	{
		bShouldUpdate = false;
		Paths.Empty();
		if (TileOn)
		{
			for (auto& Tile : TileOn->AdjacentTiles)
			{
				if (Tile && Tile->RoadOnTile)
				{
					Paths.Add(Tile->RoadOnTile);
					Tile->RoadOnTile->UpdatePaths();
				}
			}
		}
	}
}

// Called when the game starts or when spawned
void ARoad::BeginPlay()
{
	Super::BeginPlay();
	if (TileOn)
	{
		for (auto& Tile : TileOn->AdjacentTiles)
		{
			if (Tile && Tile->RoadOnTile)
			{
				Tile->RoadOnTile->bShouldUpdate = true;
			}
		}
		UpdatePaths();
	}
}

// Called every frame
void ARoad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

