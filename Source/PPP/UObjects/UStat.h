// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UStat.generated.h"


//~~~~~ Forward Declarations ~~~~~//


UCLASS(Blueprintable, BlueprintType)
class PPP_API UStat : public UObject
{
	GENERATED_BODY()
	
public:
	UStat();
	~UStat();


	FString ID;

	FString Title;

	float Value;

	float MaxValue;

	float Percentage;

	float ConsumeMultiplier;


	float Add(float Amount);

	float Subtract(float Amount);

private:

	float ClampValue();

	float UpdatePercentage();
	
};
