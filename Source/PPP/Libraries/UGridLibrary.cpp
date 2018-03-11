// Fill out your copyright notice in the Description page of Project Settings.

#include "UGridLibrary.h"


const TArray<FVector> TileDirections = {
	FVector(0, -1, 0), 
	FVector(1, 0, 0), 
	FVector(0, 1, 0),
	FVector(-1, 0, 0)
};


FVector UGridLibrary::DirectionToLocation(int32 Direction)
{
	Direction = Direction % TileDirections.Num();

	if (Direction < 0) Direction = 0;
	return TileDirections[Direction] * 50;
}

FRotator UGridLibrary::DirectionToRotation(int32 Direction)
{
	FVector Location = DirectionToLocation(Direction);
	return Location.Rotation();
}
