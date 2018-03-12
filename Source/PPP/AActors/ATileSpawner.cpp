// Fill out your copyright notice in the Description page of Project Settings.

#include "ATileSpawner.h"
#include "UObjects/UTile.h"
#include "UObjects/UGridManager.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"


// Sets default values
ATileSpawner::ATileSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUpdateTiles = false;
	CountX = 20;
	CountY = 20;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));


	static ConstructorHelpers::FObjectFinder<UStaticMesh>BaseMeshObj(TEXT("StaticMesh'/Game/PPP/Meshes/Shapes/SM_Block-50.SM_Block-50'"));
	if (BaseMeshObj.Succeeded())
	{
		MeshType = BaseMeshObj.Object;
	}
}

void ATileSpawner::CreateBlocks()
{
	if (ISMComp)
	{
		ISMComp->ClearInstances();

		float Size = 50.f;

		for (int32 y = 0; y < CountY; y++)
		{
			for (int32 x = 0; x < CountX; x++)
			{
				FRotator Rotation = FRotator(0, 0, 0);
				FVector Location = FVector(x * Size, y * Size, 0);
				FTransform Transform = FTransform(Rotation, Location);
				int32 Index = ISMComp->AddInstance(Transform);
			}
		}
	}
}

void ATileSpawner::BeginPlay()
{
	//CreateBlocks();
	Super::BeginPlay();
}

void ATileSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATileSpawner::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (bUpdateTiles)
	{
		bUpdateTiles = false;
		
		// Destroy all instance components
		TArray<UActorComponent*> currentICs = this->GetInstanceComponents();
		for (UActorComponent* ic : currentICs)
			if (ic)
				ic->DestroyComponent();
		
		/*
		if (ISMComp)
		{
			ISMComp->ClearInstances();
			ISMComp->DestroyComponent();
		}
		*/

		ISMComp = NewObject<UInstancedStaticMeshComponent>(this);
		ISMComp->RegisterComponent();
		ISMComp->SetStaticMesh(MeshType);
		ISMComp->SetFlags(RF_Transactional);
		AddInstanceComponent(ISMComp);

		CreateBlocks();
	}

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