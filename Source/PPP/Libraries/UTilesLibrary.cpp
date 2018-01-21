// Fill out your copyright notice in the Description page of Project Settings.

#include "UTilesLibrary.h"


const TArray<FVector> Directions = {
	FVector(0, -1, 0), 
	FVector(1, 0, 0), 
	FVector(0, 1, 0),
	FVector(-1, 0, 0)
};


FVector UTilesLibrary::DirectionToLocation(int32 Direction)
{
	Direction = Direction % Directions.Num();

	if (Direction < 0) Direction = 0;
	return Directions[Direction] * 50;
}

FRotator UTilesLibrary::DirectionToRotation(int32 Direction)
{
	FVector Location = DirectionToLocation(Direction);
	return Location.Rotation();
}
