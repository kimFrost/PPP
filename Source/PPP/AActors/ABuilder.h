// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StreamableManager.h"
#include "Libraries/UCustomTypesLibrary.h"
#include "ABuilder.generated.h"


//~~~~~ Forward Declarations ~~~~~//
class UArrowComponent;
class UTile;
class AStructure;
class UGridManager;


UENUM(BlueprintType)
enum class EBuilderMode : uint8
{
	VE_Structure UMETA(DisplayName = "Structure"),
	VE_Road UMETA(DisplayName = "Road")
};


UCLASS()
class PPP_API ABuilder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuilder();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Builder") //EditDefaultsOnly 
	UStaticMesh* DefaultMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Builder")
	UArrowComponent* Arrow;

	UGridManager* GridManager;

private:

	UStaticMeshComponent* Mesh;
	FStreamableManager AssetLoader;

	UTile* RootTile;
	UTile* EntranceTile;
	TArray<UTile*> TilesOn;
	int32 Rotation;
	bool bIsBuildValid;
	FST_Structure Data;
	EBuilderMode Mode;

private:

	UStaticMesh* LoadMesh(TAssetPtr<UStaticMesh> MeshAssetID);

public:

	UFUNCTION(BlueprintCallable, Category = "Builder")
	int32 Rotate(int32 Direction, UTile* Tile);

	UFUNCTION(BlueprintCallable, Category = "Builder")
	int32 SetRotation(int32 Direction, UTile* Tile);
	 
	UFUNCTION(BlueprintCallable, Category = "Builder")
	void SetData(FST_Structure& _Data);

	void SetRootTile(UTile* Tile);

	void SetMode(EBuilderMode NewMode);

	// Sizes as a array of coords 

	void UpdateTiles();
	bool ValidatePlacement();

	void Hide();
	void Show();

	AStructure* Stamp();

	//Set builder class

	// Set location on grid

	// Validate placement




protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
