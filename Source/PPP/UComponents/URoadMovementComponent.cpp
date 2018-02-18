// Fill out your copyright notice in the Description page of Project Settings.

#include "URoadMovementComponent.h"
#include "AActors/ARoad.h"
#include "AActors/AStructure.h"
#include "ACharacters/APerson.h"
#include "UObjects/UTile.h"
#include "UObjects/UTileManager.h"
#include "Libraries/UTilesLibrary.h"


URoadMovementComponent::URoadMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	TileManager = nullptr;
	RoadOn = nullptr;
	//NextTargetRoad = nullptr;
	//TargetStructure = nullptr;
	UpdatedComponent = nullptr;
	UpdatedPerson = nullptr;

	bWantsInitializeComponent = true;

	MovementSpeed = 100.f;
	bInRoadNavigation = false;
	bIsMoving = true;
}


bool URoadMovementComponent::MoveUpdatedComponentImpl(const FVector& Delta, const FQuat& NewRotation, bool bSweep, FHitResult* OutHit, ETeleportType Teleport)
{
	if (UpdatedComponent)
	{
		//const FVector NewDelta = ConstrainDirectionToPlane(Delta);
		//return UpdatedComponent->MoveComponent(NewDelta, NewRotation, bSweep, OutHit, MoveComponentFlags, Teleport);
	}

	return false;
}
void URoadMovementComponent::SetTarget(AActor* NewTarget)
{
	Target = NewTarget;
	if (Target)
	{
		TargetLocation = Target->GetActorLocation();
	}
}
void URoadMovementComponent::SetRoute(TArray<ARoad*> NewRoute)
{
	CurrentRoute = NewRoute;
	if (CurrentRoute.IsValidIndex(0))
	{
		SetTarget(CurrentRoute[0]);
		CurrentRouteIndex = 0;
		//NextTargetRoad = CurrentRoute[0];
	}
}

//~~ Virtual functions ~~//
void URoadMovementComponent::SetUpdatedComponent(USceneComponent* NewUpdatedComponent)
{
	// Don't assign pending kill components, but allow those to null out previous UpdatedComponent.
	UpdatedComponent = IsValid(NewUpdatedComponent) ? NewUpdatedComponent : NULL;
	if (UpdatedComponent)
	{
		UpdatedPerson = Cast<APerson>(UpdatedComponent->GetOwner());
	}
}
void URoadMovementComponent::InitializeComponent()
{
	TGuardValue<bool> InInitializeComponentGuard(bInInitializeComponent, true);
	Super::InitializeComponent();

	// RootComponent is null in OnRegister for blueprint (non-native) root components.
	if (!UpdatedComponent)
	{
		// Auto-register owner's root component if found.
		if (AActor* MyActor = GetOwner())
		{
			if (USceneComponent* NewUpdatedComponent = MyActor->GetRootComponent())
			{
				SetUpdatedComponent(NewUpdatedComponent);
			}
		}
	}
}

void URoadMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	
	
}
void URoadMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (UpdatedComponent)
	{
		FVector ComponentLocation = UpdatedComponent->GetComponentLocation();

		//~~ Within frame distance of TargetLocation ~~//
		if ((TargetLocation - ComponentLocation).Size() < MovementSpeed * DeltaTime)
		{
			//~~ Destination is Road ~~//
			ARoad* TargetRoad = Cast<ARoad>(Target);
			if (TargetRoad)
			{
				RoadOn = TargetRoad;
				if (UpdatedPerson)
				{
					for (auto& Entrance : RoadOn->Entrances) // Output list instead. Look for input output match
					{
						if (Entrance)
						{
							bool bGoIn = UpdatedPerson->RespondToEntrance(Entrance);
							if (bGoIn)
							{
								SetTarget(Entrance);
								break;
							}
						}
					}
				}
				if (Target == RoadOn)
				{
					if (CurrentRoute.IsValidIndex(CurrentRouteIndex + 1))
					{
						SetTarget(CurrentRoute[CurrentRouteIndex + 1]);
						CurrentRouteIndex++;
					}
					else if (CurrentRoute.Last() == Target)
					{
						SetTarget(CurrentRoute[0]);
						CurrentRouteIndex = 0;
					}
					else
					{
						bIsMoving = false;
					}
				}
			}
			else {
				//~~ Destination is Structure ~~//
				AStructure* TargetStructure = Cast<AStructure>(Target);
				if (TargetStructure)
				{
					// At structure destination. What now??
					//bIsMoving = false;

					// Interaction with structure target

					if (UpdatedPerson)
					{
						UpdatedPerson->RespondToStructure(TargetStructure);

						// Push outputs
						// Labour
						// Trading
						// Look for input/output matches
					}

					//RespondToStructure
					SetTarget(TargetStructure->TileExit->RoadOnTile);
				}
			}
		}

		//~~ Move component ~~//
		if (bIsMoving)
		{
			//~~ Set Rotation of UpdatedComponent to face TargetLocation ~~~//
			FVector LookVector = (TargetLocation - ComponentLocation).GetSafeNormal();
			UpdatedComponent->SetWorldRotation(LookVector.Rotation());

			const FVector& ForwardVector = UpdatedComponent->GetForwardVector();
			const FQuat& NewRotationQuat = UpdatedComponent->GetComponentQuat();
			const FVector& NewDelta = ForwardVector * MovementSpeed * DeltaTime; //TODO: Missing using DeltaTime
			//FHitResult* OutHit = nullptr;

			UpdatedComponent->MoveComponent(NewDelta, NewRotationQuat, false, nullptr, EMoveComponentFlags::MOVECOMP_NoFlags, ETeleportType::TeleportPhysics);
			UpdatedComponent->ComponentVelocity = FVector(100, 0, 0);

			//
			//const FVector Adjustment = FVector::VectorPlaneProject(DeltaTime, Normal) * Time;

			// Move without sweeping.
			//MoveUpdatedComponent(Adjustment, NewRotationQuat, false, nullptr, ETeleportType::TeleportPhysics);

			//bool bMoved = MoveUpdatedComponent(Adjustment, NewRotationQuat, true, &SweepOutHit, ETeleportType::TeleportPhysics);
		}
		else
		{
			UpdatedComponent->ComponentVelocity = FVector::ZeroVector;
		}
	}
	


}
