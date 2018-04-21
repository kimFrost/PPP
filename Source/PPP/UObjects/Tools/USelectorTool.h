// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObjects/Tools/UTool.h"
#include "USelectorTool.generated.h"


//~~~~~ Forward Declarations ~~~~~//
class ASelector;


//~~~~~ Deleagtes ~~~~~//



UCLASS()
class PPP_API USelectorTool : public UTool
{
	GENERATED_BODY()
	

private:

	ASelector* Visualizer;

protected:

	virtual void OnLoad_Implementation(UTool* Tool) override;
	
	
};
