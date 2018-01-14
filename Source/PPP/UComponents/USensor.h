// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "USensor.generated.h"


//~~ FORWARD DECLARATIONS ~~//
class APerson;

//~~ DELEGATES ~~//
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPersonSensored, APerson*, Person);


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PPP_API USensor : public UBoxComponent
{
	GENERATED_BODY()

public:
	USensor();
	
	
	UFUNCTION(BlueprintCallable, Category = "Sensor")
	void SensorTriggered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(BlueprintAssignable, Category = "Sensor|Module")
	FPersonSensored OnPersonSensored;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
