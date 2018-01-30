// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UTile.generated.h"


//~~~~~ Forward Declarations ~~~~~//
class UTileManager;
class ARoad;
class AStructure;

UCLASS(Blueprintable, BlueprintType)
class PPP_API UTile : public UObject
{
	GENERATED_BODY()
	
public:
	UTile();
	~UTile();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid")
	int32 X;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid")
	int32 Y;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid")
	int32 Index;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid")
	FVector WorldLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid")
	UTileManager* Manager;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid")
	TArray<UTile*> AdjacentTiles;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid")
	ARoad* RoadOnTile;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid")
	AStructure* StructureOnTile;



private:

	
};
