// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UGridManager.generated.h"


//~~~~~ Forward Declarations ~~~~~//
class UTile;


UCLASS(Blueprintable, BlueprintType)
class PPP_API UGridManager : public UObject
{
	GENERATED_BODY()
	
public:
	UGridManager();
	~UGridManager();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	int32 CountX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	int32 CountY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	float TileSize;


	UFUNCTION(BlueprintCallable, Category = "Grid")
	void CreateTiles();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Grid")
	UTile* CoordinatesToTile(int32 X, int32 Y, bool Clamp);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Grid")
	UTile* WorldLocationToTile(FVector WorldLocation);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid")
	TArray<UTile*> Tiles;

private:

	
	
};
