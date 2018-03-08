// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Libraries/UCustomTypesLibrary.h"
#include "AStructure.generated.h"



//~~~~~ Forward Declarations ~~~~~//
class UTile;
class ARoad;
class APerson;
class UStat;



UCLASS()
class PPP_API AStructure : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStructure();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Structure")
	bool bFloodFill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Structure")
	TArray<UTile*> TilesOn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Structure")
	UTile* TileEnterance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Structure")
	UTile* TileExit;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Structure")
	TArray<ARoad*> CurrentRoute;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Structure", Meta = (ExposeOnSpawn = true))
	TMap<FString, int32> SpawnStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Structure")
	TMap<FString, UStat*> Stats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Structure")
	TMap<FString, bool> States;

public:

	UFUNCTION(BlueprintCallable, Category = "Person")
	void PushPayload(const FST_Payload& Payload);


	//UClass*
	//TSubclassOf
	//TSubobjectPtr
	UFUNCTION(BlueprintCallable, Category = "Structure")
	TArray<ARoad*> GetRouteToClosetOfClass(int32 MaxRange, TSubclassOf<class AStructure> StructureClass);

	UFUNCTION(BlueprintCallable, Category = "Structure")
	void Init();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintNativeEvent)
	void Interact(APerson* Person);
	virtual void Interact_Implementation(APerson* Person);
	
	
};
