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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat", Meta = (ExposeOnSpawn = true))
	FString ID;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat", Meta = (ExposeOnSpawn = true))
	FString Title;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat", Meta = (ExposeOnSpawn = true))
	int32 Value;

	int32 MinValue;
	int32 MaxValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat")
	float Percentage;

	float ConsumeMultiplier;

	int32 Set(int32 _Value);

	int32 Add(int32 Amount);

	int32 Subtract(int32 Amount);

private:

	int32 ClampValue();

	float UpdatePercentage();
	
};


/*
UINTERFACE(Blueprintable)
class UStatInterface : public UInterface
{
    GENERATED_BODY()
};

class IStatInterface
{    
    GENERATED_BODY()

public:
    

};
*/