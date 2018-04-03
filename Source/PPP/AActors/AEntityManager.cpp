// Fill out your copyright notice in the Description page of Project Settings.

#include "AEntityManager.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"


// Sets default values
AEntityManager::AEntityManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>BaseMeshObj(TEXT("StaticMesh'/Game/PPP/Meshes/Shapes/SM_Block-50.SM_Block-50'"));
	if (BaseMeshObj.Succeeded())
	{
		MeshType = BaseMeshObj.Object;
	}
}



void AEntityManager::SpawnEntity()
{
	if (ISMComp)
	{
		FRotator Rotation = FRotator(0, 0, FMath::RandRange(0, 360));
		FVector Location = FVector(0, 0, 0);
		FTransform Transform = FTransform(Rotation, Location);
		int32 Index = ISMComp->AddInstance(Transform);
	}
}

// Called when the game starts or when spawned
void AEntityManager::BeginPlay()
{
	ISMComp = NewObject<UInstancedStaticMeshComponent>(this);
	ISMComp->RegisterComponent();
	ISMComp->SetStaticMesh(MeshType);
	ISMComp->SetFlags(RF_Transactional);
	AddInstanceComponent(ISMComp);

	GetWorld()->GetTimerManager().SetTimer(SpawnEntityTimer, this, &AEntityManager::SpawnEntity, 0.2f, true);

	/*
	if (ISMComp)
	{
		for (int32 i = 0; i < 100; i++)
		{
			FRotator Rotation = FRotator(0, 0, FMath::RandRange(0, 360));
			FVector Location = FVector(0, 0, 0);
			FTransform Transform = FTransform(Rotation, Location);
			int32 Index = ISMComp->AddInstance(Transform);
		}
	}
	*/

	Super::BeginPlay();
}

// Called every frame
void AEntityManager::Tick(float DeltaTime)
{
	if (ISMComp)
	{
		for (int32 i = 0; i < ISMComp->GetInstanceCount(); i++)
		{
			FTransform Transform;
			if (ISMComp->GetInstanceTransform(i, Transform, true))
			{
				FVector WorldLocation = Transform.GetLocation();
				FVector Direction = Transform.GetRotation().Vector();
				Transform.SetLocation(WorldLocation + (Direction * 10));
				ISMComp->UpdateInstanceTransform(i, Transform, true, true, true);
			}
		}
	}
	
	Super::Tick(DeltaTime);
}

