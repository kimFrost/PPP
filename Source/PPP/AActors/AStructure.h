// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AStructure.generated.h"



//~~~~~ Forward Declarations ~~~~~//
class UTile;
class ARoad;


UCLASS()
class PPP_API AStructure : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStructure();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Structure")
	bool bFloodFill;

	TArray<UTile*> TilesOn;

	UTile* TileEnterance;

	UTile* TileExit;


	// Route TArray<ARoad*>

	//UClass*
	//TSubclassOf
	//TSubobjectPtr
	void GetRouteToClosetOfClass(int32 MaxRange, TSubclassOf<class AStructure> StructureClass);

	void Init();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
