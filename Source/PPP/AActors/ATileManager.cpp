// Fill out your copyright notice in the Description page of Project Settings.

#include "ATileManager.h"
#include "UObjects/UTile.h"
#include "UObjects/UGridManager.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"


// Sets default values
ATileManager::ATileManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUpdateTiles = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	//AddOwnedComponent(RootScene);

	HISMComp = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("HISMComp"));
	HISMComp->SetupAttachment(RootComponent);

	//HISMComp->RegisterComponent();


	//AddOwnedComponent(HISMComp);
	//AddInstanceComponent(HISMComp);
	//HISMComp->AttachTo()
	HISMComp->SetMobility(EComponentMobility::Static);
	HISMComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HISMComp->SetFlags(RF_Transactional);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>BaseMeshObj(TEXT("StaticMesh'/Game/PPP/Meshes/Shapes/SM_Block-50.SM_Block-50'"));
	if (BaseMeshObj.Succeeded())
	{
		HISMComp->SetStaticMesh(BaseMeshObj.Object);
	}

	GridManager = CreateDefaultSubobject<UGridManager>(TEXT("GridManager"));


	//Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	//GridManager = NewObject<UGridManager>();

}

void ATileManager::CreateBlocks()
{
	if (HISMComp)
	{
		HISMComp->ClearInstances();
		if (GridManager)
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

	//RegisterAllComponents();

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




//https://docs.unrealengine.com/en-us/Programming/Tutorials/Components/1

//https://forums.unrealengine.com/development-discussion/c-gameplay-programming/40085-proper-use-of-uscenecomponents-and-registercomponent

//https://answers.unrealengine.com/questions/183439/instantiating.html?sort=oldest

//https://answers.unrealengine.com/questions/658240/c-create-a-hierarchical-instanced-static-mesh-for.html?sort=oldest