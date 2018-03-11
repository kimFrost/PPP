// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ATileManager.generated.h"


//~~~~~ Forward Declarations ~~~~~//
class UGridManager;
class UHierarchicalInstancedStaticMeshComponent;


UCLASS()
class PPP_API ATileManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileManager();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	bool bUpdateTiles;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TileManager")
	UGridManager* GridManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TileManager")
	UHierarchicalInstancedStaticMeshComponent* HISMComp;

	void CreateBlocks();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& Transform) override;
	
};
