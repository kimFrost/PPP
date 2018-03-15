// Fill out your copyright notice in the Description page of Project Settings.

#include "ATileManager.h"
#include "UObjects/UTile.h"
#include "UObjects/UGridManager.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
ATileManager::ATileManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	//PrimaryActorTick.bTickEvenWhenPaused = true;
	//bAllowTickBeforeBeginPlay = true;

	bUpdateTiles = false;
	bDrawDebugLine = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent->SetMobility(EComponentMobility::Static);
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

	/*
	// FOr components
	 PrimaryComponentTick.bCanEverTick = true;
     PrimaryComponentTick.bStartWithTickEnabled = true;
     RegisterAllComponentTickFunctions(true);
     bTickInEditor = true;
     bAutoActivate = true;
     bAutoRegister = true;
     SetComponentTickEnabled(true);
     PrimaryComponentTick.TickGroup = TG_PrePhysics; 
	*/


}

void ATileManager::CreateBlocks()
{
	if (HISMComp)
	{
		HISMComp->ClearInstances();
		if (GridManager)
		{
			for (auto& Tile : GridManager->GridTiles)
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
		//GridManager->CreateTiles();
		//CreateBlocks();
	}
	Super::BeginPlay();
}

void ATileManager::Tick(float DeltaTime)
{
	if (bDrawDebugLine)
	{
		if (GridManager)
		{
			for (auto& Tile : GridManager->GridTiles)
			{
				if (Tile)
				{
					DrawDebugBox(
						GetWorld(),
						Tile->WorldLocation,
						FVector(GridManager->TileSize / 2, GridManager->TileSize / 2, 0),
						GetRootComponent()->GetComponentToWorld().GetRotation(),
						FColor::Red,
						false,
						0.f,
						0
					);
				}
			}
		}
	}
	Super::Tick(DeltaTime);
}

void ATileManager::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	//RegisterAllComponents();

	if (bUpdateTiles)
	{
		bUpdateTiles = false;
		if (GridManager)
		{
			GridManager->CreateTiles();
			//CreateBlocks();
		}
	}

	if (bDrawDebugLine)
	{
		if (GridManager)
		{
			// Draw debug outline out grid
			for (auto& Tile : GridManager->GridTiles)
			{
				if (Tile)
				{
					/*
					DrawDebugSolidPlane(
					GetWorld(),
					FPlane(),
					Tile->WorldLocation,
					FVector2D(1, 1),
					FColor::Red,
					true,
					10.0f,
					0
					);
					*/
					DrawDebugBox(
						GetWorld(),
						Tile->WorldLocation,
						FVector(GridManager->TileSize / 2, GridManager->TileSize / 2, 0),
						GetRootComponent()->GetComponentToWorld().GetRotation(),
						FColor::Red,
						true,
						-1.f,
						0
					);
					/*
					DrawDebugSphere(
					GetWorld(),
					Tile->WorldLocation,
					25.f,
					3,
					FColor::Red,
					false,
					10.f,
					0
					);
					*/
				}
			}
		}
	}
	else
	{
		UKismetSystemLibrary::FlushPersistentDebugLines(GetWorld());
	}
	
}

/*
bool ATileManager::ShouldTickIfViewportsOnly() const
{
	return true;
}
*/



// UGridManager

// ATileManager

// ABuilder

// Loop place buildings



//https://answers.unrealengine.com/questions/292074/spawn-actor-with-expose-on-spawn-variables-in-c.html


//https://answers.unrealengine.com/questions/252259/onconstruction-c-best-practice.html

//https://docs.unrealengine.com/en-us/Programming/UnrealArchitecture/Actors/ActorLifecycle

//https://docs.unrealengine.com/en-us/Programming/Tutorials/Components/1




//https://docs.unrealengine.com/en-us/Programming/Tutorials/Components/1

//https://forums.unrealengine.com/development-discussion/c-gameplay-programming/40085-proper-use-of-uscenecomponents-and-registercomponent

//https://answers.unrealengine.com/questions/183439/instantiating.html?sort=oldest

//https://answers.unrealengine.com/questions/658240/c-create-a-hierarchical-instanced-static-mesh-for.html?sort=oldest