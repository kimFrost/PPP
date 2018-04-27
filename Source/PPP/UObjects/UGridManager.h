// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UGridManager.generated.h"


//~~~~~ Purpose ~~~~~//
/*
	ALl base grid things
	It will not spawn any actors but only set references and call delegates
*/

//~~~~~ Forward Declarations ~~~~~//
class UTile;


UCLASS(Blueprintable, BlueprintType)
class PPP_API UGridManager : public UObject
{
	GENERATED_BODY()
	
public:
	UGridManager();
	~UGridManager();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid") //Meta = (ExposeOnSpawn = true)
	int32 CountX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	int32 CountY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	float TileSize;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid")
	TArray<UTile*> GridTiles;

private:

	
	
public:

	UFUNCTION(BlueprintCallable, Category = "Grid")
	void CreateTiles(UWorld* World);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Grid")
	UTile* CoordinatesToTile(int32 X, int32 Y, bool Clamp = true);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Grid")
	UTile* WorldLocationToTile(FVector WorldLocation);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Grid")
	void GetTilesInArea(int32 X, int32 Y, int32 sizeX, int32 sizeY, TArray<UTile*>& Tiles); //UPARAM(ref)

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Grid")
	bool AreTilesFree(UPARAM(ref) const TArray<UTile*>& Tiles);

	//UFUNCTION(BlueprintCallable, Category = "Grid")
	//bool PlaceStructureOnTiles(AStructure* Structure);

	//UFUNCTION(BlueprintCallable, Category = "Grid")
	//bool PlaceRoadOnTiles(AStructure* Structure);

};

// Loop place structure one by one with 100ms interval
// Sort list by y