// Fill out your copyright notice in the Description page of Project Settings.

#include "PPPGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "UObjects/UGridManager.h"
#include "AActors/ATileManager.h"

APPPGameModeBase::APPPGameModeBase()
{
	//GridManager = CreateDefaultSubobject<UGridManager>(TEXT("GridManager"));
	//TileManager = nullptr;

	//Triggers on compile/begin play/start editor
}


UGridManager* APPPGameModeBase::GetGridManager()
{
	return GridManager;
}

ATileManager* APPPGameModeBase::GetTileManager()
{
	return TileManager;
}

void APPPGameModeBase::BeginPlay()
{
	GridManager = NewObject<UGridManager>();
	if (GridManager)
	{
		GridManager->CreateTiles();
	}

	UWorld* World = GetWorld();
	if (World)
	{
		//FActorSpawnParameters SpawnInfo;
		//SpawnInfo.bNoFail = true;
		TileManager = World->SpawnActorDeferred<ATileManager>(ATileManager::StaticClass(), FTransform(FRotator(0, 0, 0), FVector(0, 0, 0)));
		if (TileManager)
		{
			TileManager->GridManager = GridManager;
			UGameplayStatics::FinishSpawningActor(TileManager, FTransform(FRotator(0, 0, 0), FVector(0, 0, 0)));
		}
	}

	if (TileManager)
	{
		TileManager->CreateBlocks();
	}


	Super::BeginPlay();
}

void APPPGameModeBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}