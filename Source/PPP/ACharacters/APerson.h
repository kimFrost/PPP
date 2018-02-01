// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "APerson.generated.h"


//~~~~~ Forward Declarations ~~~~~//
class UTileManager;
class ARoad;


UCLASS()
class PPP_API APerson : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APerson();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person", Meta = (ExposeOnSpawn = true))
	UTileManager* TileManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Person", Meta = (ExposeOnSpawn = true))
	TArray<ARoad*> CurrentRoute;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
