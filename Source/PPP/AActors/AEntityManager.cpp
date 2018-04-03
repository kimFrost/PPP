// Fill out your copyright notice in the Description page of Project Settings.

#include "AEntityManager.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Engine.h"


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
		FRotator Rotation = FRotator(0, FMath::RandRange(0, 360), 0);
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

	GetWorld()->GetTimerManager().SetTimer(SpawnEntityTimer, this, &AEntityManager::SpawnEntity, 0.005f, true);

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
		FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), false, this);
		RV_TraceParams.bTraceAsyncScene = false;
		RV_TraceParams.bReturnPhysicalMaterial = false;

		ECollisionChannel CollisionChannel = ECC_Visibility;
		FHitResult RV_Hit(1.f);

		for (int32 i = 0; i < ISMComp->GetInstanceCount(); i++)
		{
			FTransform Transform;
			if (ISMComp->GetInstanceTransform(i, Transform, true))
			{
				FVector WorldLocation = Transform.GetLocation();
				FVector Direction = Transform.GetRotation().Vector();

				// Linetrace

				const float TraceDist = 40.f;
				const FVector LineTraceStart = WorldLocation + FVector(0, 0, 30);
				const FVector LineTraceEnd = LineTraceStart + TraceDist * FVector(0, 0, -1);

				GetWorld()->LineTraceSingleByChannel(RV_Hit, LineTraceStart, LineTraceEnd, CollisionChannel, RV_TraceParams);
				if (RV_Hit.bBlockingHit)
				{
					Transform.SetLocation(WorldLocation + (Direction * 5));
				}
				else
				{
					Transform.SetLocation(WorldLocation + (Direction * 5));
					//Transform.SetLocation(WorldLocation + (Direction * 5) + FVector(0, 0, WorldLocation.Z * 0.05 - 0.1));
				}

				ISMComp->UpdateInstanceTransform(i, Transform, true, true, true);
			}
		}

		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::FromInt(ISMComp->GetInstanceCount()));
	}
	
	
	Super::Tick(DeltaTime);
}

