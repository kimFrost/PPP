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

	UPPPGameInstance* GameInstance = Cast<UPPPGameInstance>(GetGameInstance());

	// Spawn test layout
	if (GridManager && Builder && GameInstance)
	{
		UTile* Tile = GridManager->CoordinatesToTile(5, 5);
		if (Tile)
		{
			FST_Structure* Data = GameInstance->GetStructureRowData("STRUCTURE_Residence");
			if (Data)
			{
				Builder->SetRootTile(Tile);
				Builder->SetData(*Data);
				Builder->Stamp();
			}
		}
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
	}

	if (TileManager)
	{
		TileManager->CreateBlocks();
	}
	
}
