// Fill out your copyright notice in the Description page of Project Settings.

#include "ASelector.h"
#include "Engine/StreamableManager.h"
#include "UObjects/UTile.h"
#include "AActors/AStructure.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"


// Sets default values
ASelector::ASelector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(RootScene);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	if (Mesh)
	{
		Mesh->SetupAttachment(RootComponent);
		Mesh->SetCastShadow(false);
		Mesh->SetMobility(EComponentMobility::Movable);

		static ConstructorHelpers::FObjectFinder<UStaticMesh>BaseMeshObj(TEXT("StaticMesh'/Game/PPP/Meshes/Shapes/SM_Block-50.SM_Block-50'"));
		if (BaseMeshObj.Succeeded())
		{
			Mesh->SetStaticMesh(BaseMeshObj.Object);
		}

		static ConstructorHelpers::FObjectFinder<UMaterial>MaterialObj(TEXT("/Game/PPP/Materials/M_Selector.M_Selector"));
		if (MaterialObj.Succeeded())
		{
			DynamicMaterial = UMaterialInstanceDynamic::Create(MaterialObj.Object, Mesh);
			Mesh->SetMaterial(0, DynamicMaterial);
		}
	}

}

UStaticMesh* ASelector::LoadMesh(TAssetPtr<UStaticMesh> MeshAssetID)
{
	if (MeshAssetID.IsPending())
	{
		const FStringAssetReference& AssetRef = MeshAssetID.ToSoftObjectPath();
		MeshAssetID = Cast<UStaticMesh>(AssetLoader.LoadSynchronous(AssetRef, true));
	}
	return MeshAssetID.Get();
}

void ASelector::SetTileOn(UTile* Tile)
{
	if (Tile)
	{
		TileOn = Tile;
		if (TileOn->StructureOnTile)
		{
			SetSize(TileOn->StructureOnTile->Data.Colums, TileOn->StructureOnTile->Data.Rows);
			SetActorLocation(TileOn->StructureOnTile->GetActorLocation());
		}
		else
		{
			SetSize(1, 1);
			SetActorLocation(Tile->WorldLocation);
		}
	}
}

void ASelector::SetSize(int32 X, int32 Y)
{
	if (Mesh)
	{
		Mesh->SetWorldScale3D(FVector(X, Y, 1));
	}
}

// Called when the game starts or when spawned
void ASelector::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASelector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

