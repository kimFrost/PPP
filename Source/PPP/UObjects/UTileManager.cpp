// Fill out your copyright notice in the Description page of Project Settings.

#include "UTileManager.h"
#include "UObjects/UTile.h"


UTileManager::UTileManager()
{
	CountX = 100;
	CountY = 100;
	TileSize = 50;
	 
}

UTileManager::~UTileManager()
{}

void UTileManager::CreateTiles()
{
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
				//Tile->AddToRoot(); // Prevent Garbage collection
				Tile->Index = Tiles.Add(Tile);
			}
		}
	}
}

UTile* UTileManager::CoordinatesToTile(int32 X, int32 Y)
{
	int32 _X = FMath::Clamp(X, 0, CountX);
	int32 _Y = FMath::Clamp(Y, 0, CountY);
	int32 Index = _X + _Y * CountX;
	return Tiles[Index];
}

UTile* UTileManager::WorldLocationToTile(FVector WorldLocation)
{
	int32 X = FMath::FloorToInt(WorldLocation.X / TileSize);
	int32 Y = FMath::FloorToInt(WorldLocation.Y / TileSize);
	return CoordinatesToTile(X, Y);
}