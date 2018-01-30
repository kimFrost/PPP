// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARoad.generated.h"


//~~~~~ Forward Declarations ~~~~~//
class UTile;
class AStructure;

UCLASS()
class PPP_API ARoad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoad();

	UTile* TileOn;

	bool bIsOneWay;
	int32 OneWayDirection;

	TArray<ARoad*> Paths;

	TArray<ARoad*> Neighbours;
	TArray<AStructure*> Entrances;
	TArray<AStructure*> Exits;

	void AddEntrance(AStructure* Structure);

	void AddExit(AStructure* Structure);

	bool HasEntranceOfClass(TSubclassOf<class AStructure> StructureClass);

	void UpdatePaths();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
