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

	States.Add("Drunk", false);
}

void APerson::PushPayload(const FST_Payload& Payload)
{
	for (auto& PayloadStat : Payload.Stats)
	{
		if (Stats.Contains(PayloadStat.Key))
		{
			UStat* Stat = Stats[PayloadStat.Key];
			if (Stat)
			{
				Stat->Add(PayloadStat.Value);
			}
		}
	}
	for (auto& PayloadState : Payload.States)
	{
		if (States.Contains(PayloadState.Key))
		{
			States[PayloadState.Key] = PayloadState.Value;
		}
	}
	for (auto& PayloadItem : Payload.Items)
	{

	}
}
void APerson::GetPayload(FST_Payload & Payload)
{
	for (auto& Stat : Stats)
	{
		if (Stat.Value)
		{
			Payload.Stats.Add(Stat.Key, Stat.Value->Value);
		}
	}
	Payload.States = States;
}
void APerson::Reset()
{
	for (auto& Stat : Stats)
	{
		if (Stat.Value)
		{
			Stat.Value->Set(0);
		}
	}
	for (auto& State : States)
	{
		State.Value = false;
	}
}

// Called when the game starts or when spawned
void APerson::BeginPlay()
{
	for (auto& SpawnStat : SpawnStats)
	{
		UStat* Stat = NewObject<UStat>(this);
		if (Stat)
		{
			Stat->ID = SpawnStat.Key;
			Stat->Title = SpawnStat.Key;
			Stat->Value = SpawnStat.Value;
			Stat->ConsumeMultiplier = SpawnStat.Value;
			Stats.Add(Stat->ID, Stat);
		}
	}

	//~~ This calleds the blueprint native event BeginPlay in AActor which calls beginplay in blueprint. So needs to be at the bottom ~~//
	Super::BeginPlay();
}

// Called every frame
void APerson::Tick(float DeltaTime)
{
	//GetActorForwardVector()
	//AddMovementInput(GetActorForwardVector(), 1);
	Super::Tick(DeltaTime);
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