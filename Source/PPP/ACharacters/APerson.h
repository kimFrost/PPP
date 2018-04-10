// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Libraries/UCustomTypesLibrary.h"
#include "APerson.generated.h"


//~~~~~ Forward Declarations ~~~~~//
class UGridManager;
class AStructure;
class ARoad;
class UStat;
class URoadMovementComponent;
class UNavigationTargetsMovementComponent;
class UNavigationTargetSlot;


UCLASS()
class PPP_API APerson : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APerson();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Person")
	URoadMovementComponent* RoadMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Person")
	UNavigationTargetsMovementComponent* NavigationTargetsMovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person", Meta = (ExposeOnSpawn = true))
	UGridManager* TileManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Person", Meta = (ExposeOnSpawn = true))
	TArray<ARoad*> CurrentRoute;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", Meta = (ExposeOnSpawn = true))
	TArray<UNavigationTargetSlot*> NavigationTargets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person", Meta = (ExposeOnSpawn = true))
	AStructure* Home;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
	bool bHasWorked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
	EPersonMood Mood;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
	float Energy;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person", Meta = (ExposeOnSpawn = true))
	TMap<FString, int32> SpawnStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
	TMap<FString, UStat*> Stats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
	TMap<FString, bool> States;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
	TArray<FST_PersonState> PersonStates;

	// Type: State, Skill, Wound, Item
	/*
		States: (only negatives?)
		- Drunk
		- Stressed
		- Supressed
		- Dirty
		- Mind controlled ()
		- Mutated

		Skill:
		- Strong
		Item:
		Wound:


	*/


	//FST_Payload Payload; // Instead of Stats, States and Items

	// Carrying items/goods

public:

	// static void SetRandomStreamSeed(UPARAM(ref) FRandomStream& Stream, int32 NewSeed);

	UFUNCTION(BlueprintCallable, Category = "Person")
	void PushPayload(const FST_Payload& Payload);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Person")
	void GetPayload(FST_Payload& Payload);

	UFUNCTION(BlueprintCallable, Category = "Person")
	void Reset();

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
	void RespondToStructure(AStructure* Structure);
	virtual void RespondToStructure_Implementation(AStructure* Structure);

	//virtual bool RespondToEntrance(AStructure* Entrance) const;
	

public:

	//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProductionChangedDelegate, const TArray<UResource*>&, TotalProduction);
	//FOnProductionChangedDelegate OnProductionChangedDelegate;

	UFUNCTION(BlueprintNativeEvent, Category = "Person")
	void OnStatesChanged();

};





//https://answers.unrealengine.com/questions/241909/how-to-overide-blueprintnativeevent-method-from-ba.html