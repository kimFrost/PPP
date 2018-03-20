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
			break;
		}
		case 1:
		{
			//RotatedCube = FVector{ -CubeLocal.Z, -CubeLocal.X, -CubeLocal.Y } + CenterCube;
			break;
		}
		case 2:
		{
			//RotatedCube = FVector{ CubeLocal.Y, CubeLocal.Z, CubeLocal.X } + CenterCube;
			break;
		}
		case 3:
		{
			//RotatedCube = FVector{ -CubeLocal.X, -CubeLocal.Y, -CubeLocal.Z } + CenterCube;
			break;
		}
	}

	return FVector2D();
}
