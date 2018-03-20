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
	SpawnStructureList.Add(FVector(16, 17, 0), "STRUCTURE_Factory");
	SpawnStructureList.Add(FVector(10, 6, 3), "STRUCTURE_Residence");

	SpawnStructureList.Add(FVector(16, 5, 0), "STRUCTURE_Test2x2");
	SpawnStructureList.Add(FVector(20, 5, 0), "STRUCTURE_Test3x3");
	SpawnStructureList.Add(FVector(24, 5, 0), "STRUCTURE_Test4x4");
	SpawnStructureList.Add(FVector(29, 5, 0), "STRUCTURE_Test5x2");
	SpawnStructureList.Add(FVector(35, 5, 1), "STRUCTURE_Test5x2");
	SpawnStructureList.Add(FVector(40, 5, 1), "STRUCTURE_Test2x2");


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
	SpawnRoadList.Add(FVector(13, 3, 0), "Road");
	SpawnRoadList.Add(FVector(13, 4, 0), "Road");
	SpawnRoadList.Add(FVector(13, 5, 0), "Road");
	SpawnRoadList.Add(FVector(13, 6, 0), "Road");
	SpawnRoadList.Add(FVector(13, 7, 0), "Road");
	SpawnRoadList.Add(FVector(13, 8, 0), "Road");
	SpawnRoadList.Add(FVector(13, 9, 0), "Road");
	SpawnRoadList.Add(FVector(13, 10, 0), "Road");
	SpawnRoadList.Add(FVector(13, 11, 0), "Road");
	SpawnRoadList.Add(FVector(13, 12, 0), "Road");
	SpawnRoadList.Add(FVector(13, 13, 0), "Road");
	SpawnRoadList.Add(FVector(13, 14, 0), "Road");
	SpawnRoadList.Add(FVector(13, 15, 0), "Road");
	SpawnRoadList.Add(FVector(13, 16, 0), "Road");
	SpawnRoadList.Add(FVector(13, 17, 0), "Road");
	SpawnRoadList.Add(FVector(13, 18, 0), "Road");
	SpawnRoadList.Add(FVector(13, 19, 0), "Road");
	SpawnRoadList.Add(FVector(13, 20, 0), "Road");

	SpawnRoadList.Add(FVector(5, 8, 0), "Road");
	SpawnRoadList.Add(FVector(6, 8, 0), "Road");
	SpawnRoadList.Add(FVector(7, 8, 0), "Road");
	SpawnRoadList.Add(FVector(8, 8, 0), "Road");
	SpawnRoadList.Add(FVector(9, 8, 0), "Road");
	SpawnRoadList.Add(FVector(10, 8, 0), "Road");
	SpawnRoadList.Add(FVector(11, 8, 0), "Road");
	SpawnRoadList.Add(FVector(12, 8, 0), "Road");


	UPPPGameInstance* GameInstance = Cast<UPPPGameInstance>(GetGameInstance());

	if (GridManager && Builder && GameInstance)
	{
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
		// Structures
		for (auto& Entry : SpawnStructureList)
		{
			UTile* Tile = GridManager->CoordinatesToTile(Entry.Key.X, Entry.Key.Y);
			if (Tile)
			{
				FST_Structure* Data = GameInstance->GetStructureRowData(Entry.Value);
				if (Data)
				{
					Builder->SetMode(EBuilderMode::VE_Structure);
					Builder->SetData(*Data);
					//Builder->SetRootTile(Tile);
					Builder->SetRotation(Entry.Key.Z, Tile);
					Builder->Stamp();
				}
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
