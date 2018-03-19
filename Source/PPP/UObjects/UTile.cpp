// Fill out your copyright notice in the Description page of Project Settings.

#include "UTile.h"


UTile::UTile()
{
	X = -1;
	Y = -1;
	WorldLocation = FVector(0, 0, 0);
	TileSize = 0.f;
	Manager = nullptr;
	AdjacentTiles = TArray<UTile*>();
	RoadOnTile = nullptr;
	StructureOnTile = nullptr;
}

UTile::~UTile()
{}
