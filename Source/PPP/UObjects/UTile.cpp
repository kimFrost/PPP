// Fill out your copyright notice in the Description page of Project Settings.

#include "UTile.h"


UTile::UTile()
{
	X = -1;
	Y = -1;
	WorldLocation = FVector(0, 0, 0);
	Manager = nullptr;
	AdjacentTiles = TArray<UTile*>();
}

UTile::~UTile()
{}