// Fill out your copyright notice in the Description page of Project Settings.

#include "PPPGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Libraries/UCustomTypesLibrary.h"
#include "UObjects/UTile.h"
#include "UObjects/UGridManager.h"
#include "AActors/ATileManager.h"
#include "AActors/ABuilder.h"
#include "UPPPGameInstance.h"

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
	Super::BeginPlay();


	//~~ Spawn test layout ~~//
	TMap<FVector, FString> SpawnStructureList = TMap<FVector, FString>();
	SpawnStructureList.Add(FVector(5, 5, 0), "STRUCTURE_Residence");
	SpawnStructureList.Add(FVector(10, 5, 1), "STRUCTURE_Residence");
	SpawnStructureList.Add(FVector(15, 5, 0), "STRUCTURE_Residence");

	TMap<FVector, FString> SpawnRoadList = TMap<FVector, FString>();
	SpawnRoadList.Add(FVector(10, 0, 0), "Road");
	SpawnRoadList.Add(FVector(11, 0, 0), "Road");
	SpawnRoadList.Add(FVector(10, 1, 0), "Road");
	SpawnRoadList.Add(FVector(11, 1, 0), "Road");
	SpawnRoadList.Add(FVector(10, 2, 0), "Road");
	SpawnRoadList.Add(FVector(11, 2, 0), "Road");
	SpawnRoadList.Add(FVector(12, 2, 0), "Road");
	SpawnRoadList.Add(FVector(13, 2, 0), "Road");
	SpawnRoadList.Add(FVector(14, 2, 0), "Road");
	SpawnRoadList.Add(FVector(15, 2, 0), "Road");

	UPPPGameInstance* GameInstance = Cast<UPPPGameInstance>(GetGameInstance());

	if (GridManager && Builder && GameInstance)
	{
		// Structures
		for (auto& Entry : SpawnStructureList)
		{
			UTile* Tile = GridManager->CoordinatesToTile(Entry.Key.X, Entry.Key.Y);
			if (Tile)
			{
				FST_Structure* Data = GameInstance->GetStructureRowData(Entry.Value);
				if (Data)
				{
					Builder->SetData(*Data);
					//Builder->SetRootTile(Tile);
					Builder->SetRotation(Entry.Key.Z, Tile);
					Builder->Stamp();
				}
			}
		}
		// Roads
		for (auto& Entry : SpawnRoadList)
		{
			UTile* Tile = GridManager->CoordinatesToTile(Entry.Key.X, Entry.Key.Y);
			if (Tile)
			{
				Builder->SetRootTile(Tile);
				Builder->SetMode(EBuilderMode::VE_Road);
				Builder->Stamp();
			}
		}

		TileManager->UpdateBlocks();
	}



}

void APPPGameModeBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

bool APPPGameModeBase::AllowCheats(APlayerController* P)
{
	return (GetNetMode() == NM_Standalone || GIsEditor);
	//http://zompi.pl/using-cheat-manager-in-unreal-engine-4/
}

void APPPGameModeBase::InitGame(const FString & MapName, const FString & Options, FString & ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	GridManager = NewObject<UGridManager>();
	if (GridManager)
	{
		GridManager->CreateTiles();
	}

	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.Instigator = Instigator;
		SpawnInfo.ObjectFlags |= RF_Transient;
		TileManager = World->SpawnActor<ATileManager>(ATileManager::StaticClass(), SpawnInfo);
		TileManager->GridManager = GridManager;
		/*
		TileManager = World->SpawnActorDeferred<ATileManager>(ATileManager::StaticClass(), FTransform(FRotator(0, 0, 0), FVector(0, 0, 0)));
		if (TileManager)
		{
			TileManager->GridManager = GridManager;
			UGameplayStatics::FinishSpawningActor(TileManager, FTransform(FRotator(0, 0, 0), FVector(0, 0, 0)));
		}
		*/

		Builder = World->SpawnActor<ABuilder>(ABuilder::StaticClass(), SpawnInfo);
		Builder->GridManager = GridManager;
		Builder->Hide();
	}

	if (TileManager)
	{
		TileManager->CreateBlocks();
	}
	
}
