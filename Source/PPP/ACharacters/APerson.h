// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "APerson.generated.h"


//~~~~~ Forward Declarations ~~~~~//
class UTileManager;
class AStructure;
class ARoad;


UCLASS()
class PPP_API APerson : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APerson();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person", Meta = (ExposeOnSpawn = true))
	UTileManager* TileManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Person", Meta = (ExposeOnSpawn = true))
	TArray<ARoad*> CurrentRoute;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
	bool bHasWorked;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintNativeEvent)
	bool RespondToEntrance(AStructure* Entrance);
	virtual bool RespondToEntrance_Implementation(AStructure* Entrance);

	UFUNCTION(BlueprintNativeEvent)
	bool RespondToStructure(AStructure* Structure);
	virtual bool RespondToStructure_Implementation(AStructure* Structure);

	//virtual bool RespondToEntrance(AStructure* Entrance) const;
	
};


//https://answers.unrealengine.com/questions/241909/how-to-overide-blueprintnativeevent-method-from-ba.html