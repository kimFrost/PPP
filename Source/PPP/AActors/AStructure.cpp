// Fill out your copyright notice in the Description page of Project Settings.

#include "AStructure.h"
#include "UObjects/UTile.h"
#include "ARoad.h"
#include "Libraries/UTilesLibrary.h"




// Sets default values
AStructure::AStructure()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bFloodFill = false;
}

void AStructure::GetRouteToClosetOfClass(int32 MaxRange, TSubclassOf<class AStructure> StructureClass)
{
	const TArray<FVector> Directions = {
		FVector(0, -1, 0),
		FVector(1, 0, 0),
		FVector(0, 1, 0),
		FVector(-1, 0, 0)
	};

	/*
	struct Frontier
	{
		TArray<FVector> CubeCoords;
	};
	*/

	// Not use Tarray for better performance ??

	TArray<ARoad*> Route;

	TArray<ARoad*> VisitedRoads;
	TArray<TArray<ARoad*>> Frontiers;

	if (TileExit)
	{
		if (TileExit->RoadOnTile)
		{
			//TileExit->WorldLocation;
			Frontiers.Add(TArray<ARoad*>{
				TileExit->RoadOnTile
			});
			for (int32 k = 1; k <= MaxRange; k++)
			{
				Frontiers.Add(TArray<ARoad*>());
				TArray<ARoad*>& CurrentFrontier = Frontiers[k - 1];
				for (int32 i = 0; i < CurrentFrontier.Num(); i++)
				{
					ARoad* Road = CurrentFrontier[i];
					if (Road)
					{
						VisitedRoads.Add(Road);
						if (Road->HasEntranceOfClass(StructureClass))
						{
							// Found closes target of class
							// Reverse loop though tile path and check if they exist in visitedRoads

							/*
							for (auto& Path : VisitedRoads)
							{
								Route.Push(Path);
							}
							*/
							return;
						}
						else
						{
							for (auto& Path : Road->Paths)
							{
								if (Path && !VisitedRoads.Contains(Path))
								{
									Frontiers[k].Add(Path);
								}
							}
						}
					}
				}
			}

		}

		
		// Get road on TileExit
		// Add as frontier
		// Get road destinations and add them as new frontiers



	}
}

void AStructure::Init()
{
	if (TileEnterance && TileEnterance->RoadOnTile)
	{
		TileEnterance->RoadOnTile->AddEntrance(this);
	}
	if (TileExit && TileExit->RoadOnTile)
	{
		TileExit->RoadOnTile->AddExit(this);
	}
}


// Called when the game starts or when spawned
void AStructure::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStructure::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

