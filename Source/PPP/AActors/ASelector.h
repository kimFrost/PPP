// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StreamableManager.h"
#include "ASelector.generated.h"


//~~~~~ Forward Declarations ~~~~~//
class UTile;


UCLASS()
class PPP_API ASelector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASelector();


	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Builder") //EditDefaultsOnly 
	//UStaticMesh* DefaultMesh;

private:

	UStaticMeshComponent* Mesh;
	FStreamableManager AssetLoader;
	UTile* TileOn;

private:

	UStaticMesh* LoadMesh(TAssetPtr<UStaticMesh> MeshAssetID);

public:

	UFUNCTION(BlueprintCallable, Category = "Builder")
	void SetTileOn(UTile* Tile);

	UFUNCTION(BlueprintCallable, Category = "Builder")
	void SetSize(int32 X, int32 Y);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
