// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "ATileManager.generated.h"



//~~~~~ Purpose ~~~~~//
/*
	To spawn and manage instanced tiles. 
	This will not handle any input, but will only respond to events from Grid Manager.
*/


//~~~~~ Forward Declarations ~~~~~//
class UGridManager;
class UHierarchicalInstancedStaticMeshComponent;
//class UInstancedStaticMeshComponent;

UCLASS()
class PPP_API ATileManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileManager();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileManager")
	bool bUpdateTiles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileManager")
	bool bDrawDebugLine;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TileManager")
	UGridManager* GridManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileManager")
	class UInstancedStaticMeshComponent* HISMComp;

	void CreateBlocks();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& Transform) override;
	
	//virtual bool ShouldTickIfViewportsOnly() const override;
};
