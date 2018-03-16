// Fill out your copyright notice in the Description page of Project Settings.

#include "ABuilder.h"
#include "Engine/StreamableManager.h"
#include "Components/ArrowComponent.h"
#include "Libraries/UGridLibrary.h"
#include "UObjects/UTile.h"


// Sets default values
ABuilder::ABuilder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Rotation = 0;
	bIsBuildValid = false;

	USceneComponent* RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(RootScene);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCastShadow(false);
	Mesh->SetMobility(EComponentMobility::Movable);
	/*
	static ConstructorHelpers::FObjectFinder<UStaticMesh>BaseMeshObj(TEXT("StaticMesh'/Game/Meshes/SM_HexCylinder.SM_HexCylinder'"));
	if (BaseMeshObj.Succeeded())
	{
		DefaultMesh = BaseMeshObj.Object;
		Mesh->SetStaticMesh(DefaultMesh);
	}
	*/

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	if (Arrow)
	{
		Arrow->SetupAttachment(RootComponent);
		Arrow->SetHiddenInGame(false);
		Arrow->ArrowSize = 2.1;
		Arrow->SetRelativeRotation(FRotator(0, -60.f, 0));
		Arrow->SetRelativeLocation(FVector(0, 0, 30));
		//Arrow->SetMobility(EComponentMobility::Movable);
	}
}
/*
void ABuilder::SetData(FST_Structure& Data)
{
	StructureBaseData = Data;

	//https://docs.unrealengine.com/latest/INT/Programming/Assets/ReferencingAssets/

	UStaticMesh* PreviewMesh = LoadMesh(StructureBaseData.PreviewMesh);
	if (PreviewMesh)
	{
		Mesh->SetStaticMesh(PreviewMesh);
	}
	else if (DefaultMesh)
	{
		Mesh->SetStaticMesh(DefaultMesh);
	}
}
*/

UStaticMesh* ABuilder::LoadMesh(TAssetPtr<UStaticMesh> MeshAssetID)
{
	if (MeshAssetID.IsPending())
	{
		const FStringAssetReference& AssetRef = MeshAssetID.ToSoftObjectPath();
		MeshAssetID = Cast<UStaticMesh>(AssetLoader.LoadSynchronous(AssetRef, true));
	}
	return MeshAssetID.Get();
}

int32 ABuilder::Rotate(int32 Direction, UTile * Tile)
{
	Rotation = (Rotation + 1) % 6;
	SetActorRotation(FRotator(0, Rotation * (360 / 6), 0));
	if (Tile)
	{
		SetRootTile(Tile);
	}
	UpdateTiles();
	return Rotation;
}

void ABuilder::SetRootTile(UTile* Tile)
{
	if (Tile)
	{
		FHitResult HitResult(ForceInit);
		SetActorLocation(Tile->WorldLocation, false, &HitResult, ETeleportType::TeleportPhysics);
		RootTile = Tile;
		UpdateTiles();
	}
}


void ABuilder::UpdateTiles()
{
	// If RootHex is occupied
	/*
	if (RootHex && RootHex->AttachedBuilding)
	{
		if (StructureBaseData.AttachTo.Contains(RootHex->AttachedBuilding->StructureBaseData.Id))
		{
			UHexTile* NewAttachPlacement = RootHex->GetNeighbourByOffset(UPOTLUtilFunctionLibrary::DirectionToCube(Rotation + 3)); // +3 to flip rotation
			if (NewAttachPlacement)
			{
				SetRootHex(NewAttachPlacement);
				return;
			}
		}
	}
	*/

	// Get all tiles on
	/*
	TilesOn.Empty();
	for (int32 i = 0; i < StructureBaseData.CubeSizes.Num(); i++)
	{
		FVector CubeCoord = StructureBaseData.CubeSizes[i];
		FVector RotatedCubeCoord = UPOTLUtilFunctionLibrary::RotateCube(CubeCoord, Rotation, FVector(0, 0, 0));
		UHexTile* OffsetHex = RootHex->GetNeighbourByOffset(RotatedCubeCoord);
		TilesOn.Add(OffsetHex);
		if (OffsetHex)
		{
			DrawDebugString(GetWorld(), OffsetHex->Location, "Tile", nullptr, FColor::Blue, 0.2, true);
		}
	}
	*/

	bIsBuildValid = ValidatePlacement();
}
bool ABuilder::ValidatePlacement()
{
	if (RootTile)
	{

	}
	return false;
}
void ABuilder::Hide()
{
	SetActorHiddenInGame(true);
}
void ABuilder::Show()
{
	SetActorHiddenInGame(false);
}

// Called when the game starts or when spawned
void ABuilder::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuilder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//https://www.youtube.com/watch?v=aFmLu4LSm8s