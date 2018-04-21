// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UTool.generated.h"


//~~~~~ Forward Declarations ~~~~~//
class UTool;


//~~~~~ Deleagtes ~~~~~//
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUToolOnLoaded, UTool*, Tool);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUToolOUnloaded, UTool*, Tool);



UCLASS()
class PPP_API UTool : public UObject
{
	GENERATED_BODY()
	
	

public:

	bool bIsActive;


public:

	UFUNCTION(BlueprintCallable, Category = "Tool")
	void Load();

	UFUNCTION(BlueprintCallable, Category = "Tool")
	void Unload();

	UPROPERTY(BlueprintAssignable, Category = "Tool|Event")
	FUToolOnLoaded OnToolLoadedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Tool|Event")
	FUToolOUnloaded OnToolUnloadedDelegate;

public:

	UFUNCTION(BlueprintNativeEvent)
	void OnLoad(UTool* Tool);
	virtual void OnLoad_Implementation(UTool* Tool);
	
};
