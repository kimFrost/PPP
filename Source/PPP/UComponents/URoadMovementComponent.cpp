// Fill out your copyright notice in the Description page of Project Settings.

#include "URoadMovementComponent.h"
#include "AActors/ARoad.h"
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

//~~ Virtual functions ~~//
void URoadMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	//Get root scene component 
	//UpdatedComponent = 
	
}
void URoadMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (UpdatedComponent)
	{
		const FVector& ForwardVector = UpdatedComponent->GetForwardVector();
		const FQuat& NewRotationQuat = UpdatedComponent->GetComponentQuat();
		const FVector& NewDelta = ForwardVector * 10;
		//FHitResult* OutHit = nullptr;

		UpdatedComponent->MoveComponent(NewDelta, NewRotationQuat, false, nullptr, EMoveComponentFlags::MOVECOMP_NoFlags, ETeleportType::TeleportPhysics);

		//
		//const FVector Adjustment = FVector::VectorPlaneProject(DeltaTime, Normal) * Time;

		// Move without sweeping.
		//MoveUpdatedComponent(Adjustment, NewRotationQuat, false, nullptr, ETeleportType::TeleportPhysics);

		//bool bMoved = MoveUpdatedComponent(Adjustment, NewRotationQuat, true, &SweepOutHit, ETeleportType::TeleportPhysics);
	}
	


}
