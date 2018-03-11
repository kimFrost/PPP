// Fill out your copyright notice in the Description page of Project Settings.

#include "ATileManager.h"
#include "UObjects/UTile.h"
#include "UObjects/UGridManager.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"


// Sets default values
ATileManager::ATileManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUpdateTiles = false;


	USceneComponent* RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	//HISMComp
	//HISMComp = NewObject<UHierarchicalInstancedStaticMeshComponent>(this);
	HISMComp = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("HISMComp"));
	AddInstanceComponent(HISMComp);
	HISMComp->RegisterComponent();
	//HISMComp->AttachTo()
	HISMComp->SetupAttachment(RootComponent);
	//HISMComp->SetStaticMesh(YourStaticMesh);
	HISMComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HISMComp->SetFlags(RF_Transactional);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>BaseMeshObj(TEXT("StaticMesh'/Game/PPP/Meshes/Shapes/SM_Block-50.SM_Block-50'"));
	if (BaseMeshObj.Succeeded())
	{
		HISMComp->SetStaticMesh(BaseMeshObj.Object);
	}

	RootComponent = HISMComp;

	//GridManager
	GridManager = CreateDefaultSubobject<UGridManager>(TEXT("GridManager"));
	if (GridManager)
	{
		//AddOwnedComponent(GridManager);
	}

	//Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	
	
	

	//GridManager = NewObject<UGridManager>();
}

void ATileManager::CreateBlocks()
{
	HISMComp->ClearInstances();
	if (GridManager && HISMComp)
	{
		for (auto& Tile : GridManager->Tiles)
		{
			if (Tile)
			{
				FRotator Rotation = FRotator(0, 0, 0);
				FVector Location = Tile->WorldLocation;
				FTransform Transform = FTransform(Rotation, Location);
				int32 Index = HISMComp->AddInstance(Transform);
			}
		}
	}
}

void ATileManager::BeginPlay()
{
	if (GridManager)
	{
		GridManager->CreateTiles();
		CreateBlocks();
	}
	Super::BeginPlay();
}

void ATileManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATileManager::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	/*
	if (bUpdateTiles)
	{
		bUpdateTiles = false;
		if (GridManager)
		{
			GridManager->CreateTiles();
			CreateBlocks();
		}
	}
	*/
}


//https://answers.unrealengine.com/questions/252259/onconstruction-c-best-practice.html

//https://docs.unrealengine.com/en-us/Programming/UnrealArchitecture/Actors/ActorLifecycle

//https://docs.unrealengine.com/en-us/Programming/Tutorials/Components/1