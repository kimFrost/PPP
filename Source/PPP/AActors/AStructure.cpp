// Fill out your copyright notice in the Description page of Project Settings.

#include "AStructure.h"
#include "UObjects/UTile.h"
#include "ARoad.h"
#include "UObjects/UStat.h"
#include "ACharacters/APerson.h"
#include "Libraries/UGridLibrary.h"




// Sets default values
AStructure::AStructure()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bFloodFill = false;
}

void AStructure::PushPayload(const FST_Payload& Payload)
{
	for (auto& PayloadStat : Payload.Stats)
	{
		if (Stats.Contains(PayloadStat.Key))
		{
			UStat* Stat = Stats[PayloadStat.Key];
			if (Stat)
			{
				Stat->Add(PayloadStat.Value);
			}
		}
	}
	for (auto& PayloadState : Payload.States)
	{
		if (States.Contains(PayloadState.Key))
		{
			States[PayloadState.Key] = PayloadState.Value;
		}
	}
	for (auto& PayloadItem : Payload.Items)
	{

	}
}

TArray<ARoad*> AStructure::GetRouteToClosetOfClass(int32 MaxRange, TSubclassOf<class AStructure> StructureClass)
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
							bool bAnyOnewayInRoute = false;
							Route.Push(Road);
							ARoad* CurrentRoad = Road;
							for (int32 vK = k; vK >= 0; vK--)
							{
								TArray<ARoad*>& PrevFrontier = Frontiers[vK];
								for (auto& PrevRoad : PrevFrontier)
								{
									if (PrevRoad && PrevRoad->Paths.Contains(CurrentRoad))
									{
										// If PrevRoad is oneway then set bAnyOnewayInRoute to true
										Route.Insert(PrevRoad, 0);
										CurrentRoad = PrevRoad;
										continue;
									}
								}
							}

							if (bAnyOnewayInRoute)
							{
								// Trace new back route

							}
							else
							{
								// Use same route back
								TArray<ARoad*> RouteBack;
								for (int32 vI = Route.Num() - 2; vI >= 0; vI--)
								{
									RouteBack.Add(Route[vI]);
								}
								Route.Append(RouteBack);
							}

							//[0, 1, 2, 3, 4, 5, 6]
							//[x, x, x, x, x, x, x]
							//[ , x, x, x, x, x, o]
							//[ ,  ,  , x,  , x, x]
							//[ ,  ,  ,  ,  , x, x]

							/*
							for (auto& Path : VisitedRoads)
							{
								Route.Push(Path);
							}
							*/
							return Route;
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
	return Route;
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
	for (auto& SpawnStat : SpawnStats)
	{
		UStat* Stat = NewObject<UStat>(this);
		if (Stat)
		{
			Stat->ID = SpawnStat.Key;
			Stat->Title = SpawnStat.Key;
			Stat->Value = SpawnStat.Value;
			Stat->ConsumeMultiplier = SpawnStat.Value;
			Stats.Add(Stat->ID, Stat);
		}
	}

	//~~ This calleds the blueprint native event BeginPlay in AActor which calls beginplay in blueprint. So needs to be at the bottom ~~//
	Super::BeginPlay();
}

// Called every frame
void AStructure::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);
}

void AStructure::Interact_Implementation(APerson* Person)
{}