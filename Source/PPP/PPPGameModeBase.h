// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PPPGameModeBase.generated.h"


//~~~~~ Forward Declarations ~~~~~//
class UGridManager;
class ATileManager;


UCLASS()
class PPP_API APPPGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	APPPGameModeBase();
	
private:

	UGridManager* GridManager;

	ATileManager* TileManager;

public:

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UGridManager* GetGridManager();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	ATileManager* GetTileManager();

protected:

	virtual void BeginPlay() override;

	//OnEndPlay

	virtual void OnConstruction(const FTransform& Transform) override;

};
