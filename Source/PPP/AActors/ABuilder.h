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

private:

	UStaticMeshComponent* Mesh;
	FStreamableManager AssetLoader;

	UTile* RootTile;
	TArray<UTile*> TilesOn;
	int32 Rotation;
	bool bIsBuildValid;
	FST_Structure Data;


private:

	UStaticMesh* LoadMesh(TAssetPtr<UStaticMesh> MeshAssetID);

public:

	UFUNCTION(BlueprintCallable, Category = "Builder")
	int32 Rotate(int32 Direction, UTile* Tile);
	 
	UFUNCTION(BlueprintCallable, Category = "Builder")
	void SetData(FST_Structure& _Data);

	void SetRootTile(UTile* Tile);


	// Sizes as a array of coords 

	void UpdateTiles();
	bool ValidatePlacement();

	void Hide();
	void Show();

	bool Stamp(); // Stamp a copy of the builder

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
