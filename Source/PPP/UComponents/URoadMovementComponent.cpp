// Fill out your copyright notice in the Description page of Project Settings.

#include "URoadMovementComponent.h"
#include "AActors/ARoad.h"
#include "UObjects/UTile.h"
#include "UObjects/UTileManager.h"
#include "Libraries/UTilesLibrary.h"


URoadMovementComponent::URoadMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

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


void URoadMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	
}
void URoadMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (UpdatedComponent)
	{
		const FQuat NewRotationQuat = UpdatedComponent->GetComponentQuat();
		const FVector Adjustment = FVector::VectorPlaneProject(DeltaTime, Normal) * Time;

		// Move without sweeping.
		MoveUpdatedComponent(Adjustment, NewRotationQuat, false, nullptr, ETeleportType::TeleportPhysics);

		//bool bMoved = MoveUpdatedComponent(Adjustment, NewRotationQuat, true, &SweepOutHit, ETeleportType::TeleportPhysics);
	}
	


}
