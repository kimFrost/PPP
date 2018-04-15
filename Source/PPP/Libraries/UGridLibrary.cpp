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
	Direction = (Direction + 1) % TileDirections.Num();

	FVector Location = DirectionToLocation(Direction);
	return Location.Rotation();
}

int32 UGridLibrary::RotationToDirection(FRotator Rotation)
{
	//Rotation.Vector();
	//return TileDirections

	return int32();
}



FVector2D UGridLibrary::RotateCoord(FVector2D Coord, int32 Rotation)
{
	//return Coord.GetRotated(DirectionToRotation(Rotation).Yaw); 
	Rotation = Rotation % TileDirections.Num();

	//(-3, -1);
	//(1, -3)
	//(3, 1)
	//(-1, 3)

	switch (Rotation)
	{
		case 0:
		{
			return Coord;
		}
		case 1:
		{
			return FVector2D{ Coord.Y * -1, Coord.X };
		}
		case 2:
		{
			return FVector2D{ Coord.X * -1, Coord.Y * -1 };
		}
		case 3:
		{
			return FVector2D{ Coord.Y, Coord.X * -1 };
		}
	}
	return Coord;
}


