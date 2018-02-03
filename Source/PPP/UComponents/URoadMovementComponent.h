// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "URoadMovementComponent.generated.h"


//~~~~~ Forward Declarations ~~~~~//
class UTileManager;
class ARoad;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PPP_API URoadMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URoadMovementComponent();

	UTileManager* TileManager;

	ARoad* RoadOn;

	ARoad* NextTargetRoad;

	USceneComponent* UpdatedComponent;

	TArray<ARoad*> CurrentRoute;

	float MovementSpeed;

	float Velocity;

	//GetRoute


protected:

	virtual bool MoveUpdatedComponentImpl(const FVector& Delta, const FQuat& NewRotation, bool bSweep, FHitResult* OutHit = NULL, ETeleportType Teleport = ETeleportType::None);

	virtual void BeginPlay() override;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};