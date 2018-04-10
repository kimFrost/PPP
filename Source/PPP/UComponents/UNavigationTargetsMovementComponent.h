// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UNavigationTargetsMovementComponent.generated.h"


//~~~~~ Forward Declarations ~~~~~//
class APerson;
class AStructure;
class UNavigationTargetSlot;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PPP_API UNavigationTargetsMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNavigationTargetsMovementComponent();


	AStructure* PrevTarget;
	AStructure* Target;

	FVector TargetLocation;

	USceneComponent* UpdatedComponent;

	APerson* UpdatedPerson;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", Meta = (ExposeOnSpawn = true))
	TArray<UNavigationTargetSlot*> NavigationTargets;

	TArray<AStructure*> StructureList;


	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MovementSpeedModifier;

	float Velocity;

	bool bIsMoving;

	int32 CurrentTargetIndex;

	UFUNCTION(BlueprintCallable, Category = "Components|Movement")
	void SetTarget(AStructure* NewTarget);

	UFUNCTION(BlueprintCallable, Category = "Components|Movement")
	void SetTargets(TArray<UNavigationTargetSlot*> NewTargets);

	void ProgressToNextTarget();

	UFUNCTION(BlueprintCallable, Category = "Components|Movement")
	virtual void SetUpdatedComponent(USceneComponent* NewUpdatedComponent);

protected:

	bool bInInitializeComponent;

	virtual void InitializeComponent() override;

	virtual void BeginPlay() override;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
