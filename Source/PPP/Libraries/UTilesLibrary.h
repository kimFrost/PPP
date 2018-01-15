// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UTilesLibrary.generated.h"

/**
 * 
 */
UCLASS()
class PPP_API UTilesLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Util")
	static FVector DirectionToLocation(int32 Direction);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Util")
	static FRotator DirectionToRotation(int32 Direction);

};
