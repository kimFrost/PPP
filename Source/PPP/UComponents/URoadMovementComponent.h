// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "URoadMovementComponent.generated.h"


//~~~~~ Forward Declarations ~~~~~//
class UGridManager;
class APerson;
class AStructure;
class ARoad;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PPP_API URoadMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URoadMovementComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", Meta = (ExposeOnSpawn = true))
	UGridManager* GridManager;

	ARoad* RoadOn;

	AActor* PrevTarget;
	AActor* Target;
	//ARoad* NextTargetRoad;
	//AStructure* TargetStructure;

	FVector TargetLocation;

	USceneComponent* UpdatedComponent;

	APerson* UpdatedPerson;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", Meta = (ExposeOnSpawn = true))
	TArray<ARoad*> CurrentRoute;


	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MovementSpeedModifier;

	float Velocity;

	bool bInRoadNavigation;
	bool bIsMoving;
	bool bReverse;

	int32 CurrentRouteIndex;

	UFUNCTION(BlueprintCallable, Category = "Components|Movement")
	void SetTarget(AActor* NewTarget);

	UFUNCTION(BlueprintCallable, Category = "Components|Movement")
	void SetRoute(TArray<ARoad*> NewRoute);

	UFUNCTION(BlueprintCallable, Category = "Components|Movement")
	virtual void SetUpdatedComponent(USceneComponent* NewUpdatedComponent);

protected:

	bool bInInitializeComponent;

	virtual bool MoveUpdatedComponentImpl(const FVector& Delta, const FQuat& NewRotation, bool bSweep, FHitResult* OutHit = NULL, ETeleportType Teleport = ETeleportType::None);

	virtual void InitializeComponent() override;

	virtual void BeginPlay() override;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
