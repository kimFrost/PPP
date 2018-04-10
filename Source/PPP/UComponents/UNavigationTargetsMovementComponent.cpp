// Fill out your copyright notice in the Description page of Project Settings.

#include "UNavigationTargetsMovementComponent.h"
#include "CollisionQueryParams.h"
#include "UObjects/UNavigationTargetSlot.h"
#include "AActors/AStructure.h"
#include "ACharacters/APerson.h"


UNavigationTargetsMovementComponent::UNavigationTargetsMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	UpdatedComponent = nullptr;
	UpdatedPerson = nullptr;

	bWantsInitializeComponent = true;

	MovementSpeed = 100.f;
	MovementSpeedModifier = 1.f;
	bIsMoving = true;
}


void UNavigationTargetsMovementComponent::SetTarget(AStructure* NewTarget)
{
	PrevTarget = Target;
	Target = NewTarget;
	if (Target)
	{
		TargetLocation = Target->GetActorLocation();
	}
}
void UNavigationTargetsMovementComponent::SetTargets(TArray<UNavigationTargetSlot*> NewTargets)
{
	NavigationTargets = NewTargets;
	StructureList.Empty();
	for (auto& Slot : NavigationTargets)
	{
		if (Slot && Slot->Allocated)
		{
			StructureList.Add(Slot->Allocated);
		}
	}
	if (StructureList.IsValidIndex(0))
	{
		SetTarget(StructureList[0]);
		CurrentTargetIndex = 0;
	}
}

void UNavigationTargetsMovementComponent::ProgressToNextTarget()
{
	if (StructureList.IsValidIndex(CurrentTargetIndex + 1))
	{
		if (StructureList[CurrentTargetIndex + 1])
		{
			SetTarget(StructureList[CurrentTargetIndex + 1]);
		}
	}
	else if (UpdatedPerson->Home)
	{
		// Return home instead of going to first entry
		SetTarget(UpdatedPerson->Home);
	}
	else
	{
		bIsMoving = false;
	}
}

//~~ Virtual functions ~~//
void UNavigationTargetsMovementComponent::SetUpdatedComponent(USceneComponent* NewUpdatedComponent)
{
	// Don't assign pending kill components, but allow those to null out previous UpdatedComponent.
	UpdatedComponent = IsValid(NewUpdatedComponent) ? NewUpdatedComponent : NULL;
	if (UpdatedComponent)
	{
		UpdatedPerson = Cast<APerson>(UpdatedComponent->GetOwner());
	}
}
void UNavigationTargetsMovementComponent::InitializeComponent()
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

void UNavigationTargetsMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}
void UNavigationTargetsMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (UpdatedComponent)
	{
		FVector ComponentLocation = UpdatedComponent->GetComponentLocation();

		bIsMoving = true;

		//~~ Within frame distance of TargetLocation ~~//
		if ((TargetLocation - ComponentLocation).Size() < MovementSpeed * MovementSpeedModifier * DeltaTime)
		{
			if (Target && UpdatedPerson)
			{
				Target->Interact(UpdatedPerson);
				ProgressToNextTarget();
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
			const FVector& NewDelta = ForwardVector * MovementSpeed * MovementSpeedModifier * DeltaTime;

			UpdatedComponent->MoveComponent(NewDelta, NewRotationQuat, false, nullptr, EMoveComponentFlags::MOVECOMP_NoFlags, ETeleportType::TeleportPhysics);
			UpdatedComponent->ComponentVelocity = FVector(MovementSpeed * MovementSpeedModifier, 0, 0);
		}
		else
		{
			UpdatedComponent->ComponentVelocity = FVector::ZeroVector;
		}
	}
	


}
