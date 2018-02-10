// Fill out your copyright notice in the Description page of Project Settings.

#include "URoadMovementComponent.h"
#include "AActors/ARoad.h"
#include "AActors/AStructure.h"
#include "UObjects/UTile.h"
#include "UObjects/UTileManager.h"
#include "Libraries/UTilesLibrary.h"


URoadMovementComponent::URoadMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	TileManager = nullptr;
	RoadOn = nullptr;
	NextTargetRoad = nullptr;
	UpdatedComponent = nullptr;

	bWantsInitializeComponent = true;

	MovementSpeed = 100.f;
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
void URoadMovementComponent::SetRoute(TArray<ARoad*> NewRoute)
{
	CurrentRoute = NewRoute;
	if (CurrentRoute.IsValidIndex(0))
	{
		NextTargetRoad = CurrentRoute[0];
		CurrentRouteIndex = 0;
	}
}

//~~ Virtual functions ~~//
void URoadMovementComponent::SetUpdatedComponent(USceneComponent* NewUpdatedComponent)
{
	// Don't assign pending kill components, but allow those to null out previous UpdatedComponent.
	UpdatedComponent = IsValid(NewUpdatedComponent) ? NewUpdatedComponent : NULL;
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
		if (NextTargetRoad)
		{
			FVector RoadLocation = NextTargetRoad->GetActorLocation();
			FVector ComponentLocation = UpdatedComponent->GetComponentLocation();
			//~~ Within frame distance of  NextTargetRoad ~~//
			if ((RoadLocation - ComponentLocation).Size() < MovementSpeed * DeltaTime) //TODO: Missing using DeltaTime
			{
				RoadOn = NextTargetRoad;
				for (auto& Entrance : RoadOn->Entrances)
				{
					if (Entrance)
					{
						//


						// parse entraces

						// Check if go into and come back after a while and resume route

						// If factory


					}
				}
				//int32 CurrentIndex = CurrentRoute.IndexOfByKey(NextTargetRoad);
				if (CurrentRoute.IsValidIndex(CurrentRouteIndex + 1))
				{
					NextTargetRoad = CurrentRoute[CurrentRouteIndex + 1]; // Set next target road
					CurrentRouteIndex++;
				}
				else if (CurrentRoute.Last() == NextTargetRoad) 
				{
					// At end
					//bIsMoving = false;
					//NextTargetRoad = nullptr;
					NextTargetRoad = CurrentRoute[0];
					CurrentRouteIndex = 0;
				}
			}
			// Set Rotation of UpdatedComponent to face NextTargetRoad
			FVector LookVector = (RoadLocation - ComponentLocation).GetSafeNormal();
			UpdatedComponent->SetWorldRotation(LookVector.Rotation());

			bIsMoving = true;
		}
		else
		{
			bIsMoving = false;
		}
		if (bIsMoving)
		{
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
