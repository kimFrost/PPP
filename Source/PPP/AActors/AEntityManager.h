// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AEntityManager.generated.h"



//~~~~~ Forward Declarations ~~~~~//
class UHierarchicalInstancedStaticMeshComponent;
class UInstancedStaticMeshComponent;



UCLASS()
class PPP_API AEntityManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEntityManager();

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileSpawner")
	UStaticMesh* MeshType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileSpawner")
	UInstancedStaticMeshComponent* ISMComp;

private:

	void SpawnEntity();

	FTimerHandle SpawnEntityTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	
};
