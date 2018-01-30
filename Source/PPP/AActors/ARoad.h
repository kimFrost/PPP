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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Road")
	UTile* TileOn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Road")
	bool bIsOneWay;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Road")
	int32 OneWayDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Road")
	TArray<ARoad*> Paths;

	TArray<ARoad*> Neighbours;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Road")
	TArray<AStructure*> Entrances;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Road")
	TArray<AStructure*> Exits;

	void AddEntrance(AStructure* Structure);

	void AddExit(AStructure* Structure);

	bool HasEntranceOfClass(TSubclassOf<class AStructure> StructureClass);

	UFUNCTION(BlueprintCallable, Category = "Road")
	void UpdatePaths();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
