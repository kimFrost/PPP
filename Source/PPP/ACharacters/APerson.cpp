// Fill out your copyright notice in the Description page of Project Settings.

#include "APerson.h"
#include "Libraries/UCustomTypesLibrary.h"
#include "UObjects/UStat.h"
#include "AActors/AStructure.h"


// Sets default values
APerson::APerson()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bHasWorked = false;
	Mood = EPersonMood::VE_Neutral;
	Energy = 1;

	SpawnStats.Add("Stress", 0);
	SpawnStats.Add("Money", 0);
	SpawnStats.Add("Wellness", 0);

	//States.Add("Drunk", true);
}

// Called when the game starts or when spawned
void APerson::BeginPlay()
{
	Super::BeginPlay();
	
	for (auto& SpawnStat : SpawnStats)
	{
		UStat* Stat = NewObject<UStat>(this);
		if (Stat)
		{
			Stat->ID = SpawnStat.Key;
			Stat->Value = SpawnStat.Value;
			Stat->ConsumeMultiplier = SpawnStat.Value;
			Stats.Add(Stat->ID, Stat);
		}
	}
}

// Called every frame
void APerson::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//GetActorForwardVector()
	//AddMovementInput(GetActorForwardVector(), 1);
}

// Called to bind functionality to input
void APerson::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}



bool APerson::RespondToEntrance_Implementation(AStructure* Entrance)
{
	return false;
}
void APerson::RespondToStructure_Implementation(AStructure* Entrance)
{}