// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ABuildingPlayerController.generated.h"



//~~~~~ Forward Declarations ~~~~~//
class ASelector;
class ABuilder;


UCLASS()
class PPP_API ABuildingPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:

	ASelector* Selector;
	
	ABuilder* Builder;

public:

	virtual void Tick(float DeltaTime) override;

};
