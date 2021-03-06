// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UGridLibrary.generated.h"

/**
 * 
 */
UCLASS()
class PPP_API UGridLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Util")
	static FVector DirectionToLocation(int32 Direction);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Util")
	static FRotator DirectionToRotation(int32 Direction);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Util")
	static int32 RotationToDirection(FRotator Rotation);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Util")
	static FVector2D RotateCoord(FVector2D Coord, int32 Rotation);


};
