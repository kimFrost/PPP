// Fill out your copyright notice in the Description page of Project Settings.

#include "APerson.h"
#include "Libraries/UCustomTypesLibrary.h"
#include "UObjects/UStat.h"
#include "UObjects/UNavigationTargetSlot.h"
#include "AActors/AStructure.h"
#include "UPPPGameInstance.h"
#include "UComponents/URoadMovementComponent.h"
#include "UComponents/UNavigationTargetsMovementComponent.h"


// Sets default values
APerson::APerson()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Home = nullptr;
	bHasWorked = false;
	Mood = EPersonMood::VE_Neutral;
	Energy = 1;

	SpawnStats.Add("Health", 5);

	SpawnStats.Add("Stress", 0);
	SpawnStats.Add("Money", 0);
	SpawnStats.Add("Wellness", 0);

	States.Add("Drunk", false);

	NavigationTargetsMovementComponent = CreateDefaultSubobject<UNavigationTargetsMovementComponent>(TEXT("NavigationTargetsMovementComponent"));

	/*
	RoadMovementComponent = CreateDefaultSubobject<URoadMovementComponent>(TEXT("RoadMovementComponent"));
	if (RoadMovementComponent)
	{
		//AddOwnedComponent(RoadMovementComponent);
	}
	*/
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
		else
		{
			States.Add(PayloadState.Key, PayloadState.Value);
		}
	}
	for (auto& PayloadItem : Payload.Items)
	{

	}

	float MovementSpeedModifier = 1.f;
	// parse stats and states with interaction data table
	UPPPGameInstance* GameInstance = Cast<UPPPGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		for (auto& PayloadState : Payload.States)
		{
			if (PayloadState.Value == true)
			{
				FST_PersonState* PersonState = GameInstance->GetPersonStateRowData(PayloadState.Key);
				if (PersonState)
				{
					PersonStates.Add(*PersonState);
					for (auto& Effect : PersonState->Effects)
					{
						MovementSpeedModifier = MovementSpeedModifier * Effect.Value;
					}
				}
			}
			else
			{
				for (int32 i = 0; i < PersonStates.Num(); i++)
				{
					FST_PersonState& PersonState = PersonStates[i];
					if (PersonState.ID == PayloadState.Key)
					{
						PersonStates.RemoveAt(i);
						break;
					}
				}
			}
		}
	}
	if (RoadMovementComponent)
	{
		RoadMovementComponent->MovementSpeedModifier = MovementSpeedModifier;
	}
	if (NavigationTargetsMovementComponent)
	{
		NavigationTargetsMovementComponent->MovementSpeedModifier = MovementSpeedModifier;
	}

	// Loop states
	OnStatesChanged();
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
	OnStatesChanged();
}

void APerson::Kill()
{
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

	if (RoadMovementComponent)
	{
		RoadMovementComponent->SetRoute(CurrentRoute);
	}
	if (NavigationTargetsMovementComponent)
	{
		NavigationTargetsMovementComponent->SetTargets(NavigationTargets);
	}

	//~~ This calleds the blueprint native event BeginPlay in AActor which calls beginplay in blueprint. So needs to be at the bottom ~~//
	Super::BeginPlay();
}

void APerson::OnStatesChanged_Implementation()
{}

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