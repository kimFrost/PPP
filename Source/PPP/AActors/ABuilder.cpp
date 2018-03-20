// Fill out your copyright notice in the Description page of Project Settings.

#include "ABuilder.h"
#include "Engine/StreamableManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Libraries/UCustomTypesLibrary.h"
#include "Libraries/UGridLibrary.h"
#include "UObjects/UTile.h"
#include "UObjects/UGridManager.h"
#include "AActors/AStructure.h"
#include "AActors/ARoad.h"


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
	if (Mesh)
	{
		Mesh->SetupAttachment(RootComponent);
		Mesh->SetCastShadow(false);
		Mesh->SetMobility(EComponentMobility::Movable);
	}
	
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

UStaticMesh* ABuilder::LoadMesh(TAssetPtr<UStaticMesh> MeshAssetID)
{
	if (MeshAssetID.IsPending())
	{
		const FStringAssetReference& AssetRef = MeshAssetID.ToSoftObjectPath();
		MeshAssetID = Cast<UStaticMesh>(AssetLoader.LoadSynchronous(AssetRef, true));
	}
	return MeshAssetID.Get();
}

int32 ABuilder::Rotate(int32 Direction, UTile* Tile)
{
	Rotation = (Rotation + Direction) % 4;
	SetRotation(Rotation, Tile);
	return Rotation;
}

int32 ABuilder::SetRotation(int32 Direction, UTile* Tile)
{
	Rotation = (Rotation + Direction) % 4;
	SetActorRotation(UGridLibrary::DirectionToRotation(Direction));
	if (Tile)
	{
		SetRootTile(Tile);
	}
	UpdateTiles();
	return Rotation;
}

void ABuilder::SetData(FST_Structure& _Data)
{
	Data = _Data;

	//https://docs.unrealengine.com/latest/INT/Programming/Assets/ReferencingAssets/

	UStaticMesh* PreviewMesh = LoadMesh(Data.PreviewMesh);
	if (PreviewMesh)
	{
		Mesh->SetStaticMesh(PreviewMesh);
	}
	else if (DefaultMesh)
	{
		Mesh->SetStaticMesh(DefaultMesh);
	}
}

void ABuilder::SetRootTile(UTile* Tile)
{
	if (Tile && GridManager)
	{
		FHitResult HitResult(ForceInit);
		FVector WorldLocation = Tile->WorldLocation;
		if (Rotation % 2 > 0)
		{
			if (Data.Rows % 2 == 0)
			{
				WorldLocation -= FVector(GridManager->TileSize / 2, 0, 0);
			}
			if (Data.Colums % 2 == 0)
			{
				WorldLocation -= FVector(0, GridManager->TileSize / 2, 0);
			}
		}
		else
		{
			if (Data.Colums % 2 == 0)
			{
				WorldLocation -= FVector(GridManager->TileSize / 2, 0, 0);
			}
			if (Data.Rows % 2 == 0)
			{
				WorldLocation -= FVector(0, GridManager->TileSize / 2, 0);
			}
		}
		SetActorLocation(WorldLocation, false, &HitResult, ETeleportType::TeleportPhysics);
		RootTile = Tile;
		UpdateTiles();
	}
}

void ABuilder::SetMode(EBuilderMode NewMode)
{
	Mode = NewMode;
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

	// Get Most center tile
	/*
	if (GridManager)
	{
		RootTile = GridManager->WorldLocationToTile(GetActorLocation());
	}
	*/


	//~~ Get all tiles on ~~//
	TilesOn.Empty();
	if (GridManager && RootTile)
	{
		if (Rotation % 2 > 0)
		{
			GridManager->GetTilesInArea(RootTile->X, RootTile->Y, Data.Rows, Data.Colums, TilesOn);
		}
		else
		{
			GridManager->GetTilesInArea(RootTile->X, RootTile->Y, Data.Colums, Data.Rows, TilesOn);
		}
		/*
		for (int32 Y = 0; Y < Data.Rows; Y++)
		{
			for (int32 X = 0; X < Data.Colums; X++)
			{
				// Maybe X, Y Start at 1 and <=
				int32 TileX = RootTile->X + X - FMath::FloorToInt(Data.Colums / 2);
				int32 TileY = RootTile->Y + Y - FMath::FloorToInt(Data.Rows / 2);
				if (Rotation % 2 > 0)
				{
					int32 _TileX = TileX;
					int32 _TileY = TileY;
					TileX = _TileY;
					TileY = _TileX;
				}
				UTile* Tile = GridManager->CoordinatesToTile(TileX, TileY);
				if (Tile)
				{
					TilesOn.Add(Tile);
				}
			}
		}
		*/
	}

	//~~ Entrance Tile ~~//
	if (RootTile && GridManager)
	{
		FVector2D EntraceCoord = FVector2D(RootTile->X + Data.EntranceCoord.X, RootTile->Y + Data.EntranceCoord.Y);
		EntraceCoord = UGridLibrary::RotateCoord(EntraceCoord, Rotation);
		EntranceTile = GridManager->CoordinatesToTile(EntraceCoord.X, EntraceCoord.Y, false);
		
	}

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

AStructure* ABuilder::Stamp()
{
	// Spawn clone
	UWorld* World = GetWorld();
	if (World)
	{
		if (Mode == EBuilderMode::VE_Structure)
		{
			//FActorSpawnParameters SpawnInfo;
			//SpawnInfo.Instigator = Instigator;
			//SpawnInfo.ObjectFlags |= RF_Transient;
			//SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			FTransform Transform = FTransform(GetActorRotation(), GetActorLocation());
			AStructure* Structure = World->SpawnActorDeferred<AStructure>(Data.StructureClass, Transform, nullptr, Instigator, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
			if (Structure)
			{
				for (auto& Tile : TilesOn)
				{
					if (Tile)
					{
						Tile->StructureOnTile = Structure;
					}
				}
				Structure->TilesOn = TilesOn;
				Structure->Data = Data;
				Structure->TempRootTile = RootTile;
				Structure->TileEntrance = EntranceTile;
				Structure->TileExit = EntranceTile;

				UGameplayStatics::FinishSpawningActor(Structure, Transform);
				return Structure;
			}
		}
		else if (Mode == EBuilderMode::VE_Road)
		{
			FTransform Transform = FTransform(GetActorRotation(), GetActorLocation());
			ARoad* Road = World->SpawnActorDeferred<ARoad>(ARoad::StaticClass() , Transform, nullptr, Instigator, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
			if (Road)
			{
				if (RootTile)
				{
					Road->TileOn = RootTile;
					RootTile->RoadOnTile = Road;
				}
				UGameplayStatics::FinishSpawningActor(Road, Transform);
			}
		}
	}
	return nullptr;
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