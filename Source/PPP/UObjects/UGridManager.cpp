// Fill out your copyright notice in the Description page of Project Settings.

#include "UGridManager.h"
#include "UObjects/UTile.h"
#include "Libraries/UGridLibrary.h"


const TArray<FVector> TileDirections = {
	FVector(0, -1, 0),
	FVector(1, 0, 0),
	FVector(0, 1, 0),
	FVector(-1, 0, 0)
};

UGridManager::UGridManager()
{
	CountX = 100;
	CountY = 100;
	TileSize = 50;
	 
}

UGridManager::~UGridManager()
{}

void UGridManager::CreateTiles()
{
	GridTiles.Empty();

	for (int32 Y = 0; Y < CountY; Y++)
	{
		for (int32 X = 0; X < CountX; X++)
		{
			FVector Location = FVector(X * TileSize, Y * TileSize, 0);
			UTile* Tile = NewObject<UTile>();
			if (Tile)
			{
				Tile->X = X;
				Tile->Y = Y;
				Tile->WorldLocation = Location;
				Tile->Manager = this;
				Tile->TileSize = TileSize;
				//Tile->AddToRoot(); // Prevent Garbage collection
				Tile->Index = GridTiles.Add(Tile);
			}
		}
	}

	//~~ Set Adjacent tiles in each tile ~~//
	for (auto& Tile : GridTiles)
	{
		if (Tile)
		{
			for (auto& Direction : TileDirections)
			{
				UTile* NeighbourTile = CoordinatesToTile(Tile->X + Direction.X, Tile->Y + Direction.Y, false);
				if (NeighbourTile && NeighbourTile != Tile)
				{
					Tile->AdjacentTiles.Add(NeighbourTile);
				}
				else {
					Tile->AdjacentTiles.Add(nullptr);
				}
			}
		}
	}

}
UTile* UGridManager::CoordinatesToTile(int32 X, int32 Y, bool Clamp)
{
	int32 _X = X;
	int32 _Y = Y;
	if (Clamp)
	{
		_X = FMath::Clamp(X, 0, CountX - 1);
		_Y = FMath::Clamp(Y, 0, CountY - 1);
	}
	int32 Index = _X + _Y * CountX;
	if (GridTiles.IsValidIndex(Index))
	{
		return GridTiles[Index];
	}
	return nullptr;
}
UTile* UGridManager::WorldLocationToTile(FVector WorldLocation)
{
	// If on edge between tiles, then rounds up // (25 + 50 / 2) / 50 == 1, not 0
	int32 X = FMath::FloorToInt((WorldLocation.X + TileSize / 2) / TileSize);
	int32 Y = FMath::FloorToInt((WorldLocation.Y + TileSize / 2) / TileSize);
	return CoordinatesToTile(X, Y);
}
void UGridManager::GetTilesInArea(int32 X, int32 Y, int32 sizeX, int32 sizeY, TArray<UTile*>& Tiles)
{
	for (int32 _Y = 0; _Y < sizeY; _Y++)
	{
		for (int32 _X = 0; _X < sizeX; _X++)
		{
			int32 TileX = X + _X - FMath::FloorToInt(sizeX / 2);
			int32 TileY = Y + _Y - FMath::FloorToInt(sizeY / 2);
		
			UTile* Tile = CoordinatesToTile(TileX, TileY);
			//UTile* Tile = CoordinatesToTile(_X + X, _Y + Y);
			if (Tile)
			{
				Tiles.Add(Tile); 
			}
		}
	}
}
bool UGridManager::AreTilesFree(UPARAM(ref) const TArray<UTile*>& Tiles)
{
	for (auto& Tile : GridTiles)
	{
		if (Tile)
		{
			if (Tile->RoadOnTile || Tile->StructureOnTile)
			{
				return false;
			}
		}
	}
	return true;
}
