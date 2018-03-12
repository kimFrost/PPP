// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ATileSpawner.generated.h"


//~~~~~ Forward Declarations ~~~~~//
class UHierarchicalInstancedStaticMeshComponent;
class UInstancedStaticMeshComponent;


UCLASS()
class PPP_API ATileSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileSpawner();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileSpawner")
	int32 CountX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileSpawner")
	int32 CountY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileSpawner")
	bool bUpdateTiles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileSpawner")
	UStaticMesh* MeshType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileSpawner")
	UInstancedStaticMeshComponent* ISMComp;

	void CreateBlocks();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& Transform) override;
	
};
