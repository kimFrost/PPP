// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UNavigationTargetSlot.generated.h"


//~~~~~ Forward Declarations ~~~~~//
class UNavigationTargetSlot;
class AStructure;


//~~~~~ Deleagtes ~~~~~//
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUNavigationTargetSlotOnUnallocation, UNavigationTargetSlot*, AllocationSlot, AStructure*, Allocatable);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUNavigationTargetSlotOnAllocation, UNavigationTargetSlot*, AllocationSlot, AStructure*, Allocatable);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUNavigationTargetSlotOnChange, UNavigationTargetSlot*, AllocationSlot, AStructure*, Allocatable);
//DECLARE_DELEGATE_RetVal_TwoParams(AActor*, FUNavigationTargetSlotRequest, UClass*, FString);


UCLASS(Blueprintable, BlueprintType)
class PPP_API UNavigationTargetSlot : public UObject
{
	GENERATED_BODY()

public:
	UNavigationTargetSlot();
	~UNavigationTargetSlot();

	//TSubclassOf<class UAllocatable> AllowedAllocationClass;
	UClass* AllowedAllocationClass;
	FString AllowedAllocationID;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Allocation")
	AStructure* Allocated;

	AStructure* PrevAllocated;

public:

	UFUNCTION(BlueprintCallable, Category = "Allocation")
	void Allocate(AStructure* Structure);
	
	UFUNCTION(BlueprintCallable, Category = "Allocation")
	void Unallocate(AStructure* Structure = nullptr);

public:

	//FUNavigationTargetSlotRequest OnRequestAllocatable;

	UPROPERTY(BlueprintAssignable, Category = "Allocation|Event")
	FUNavigationTargetSlotOnUnallocation OnUnallocationDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Allocation|Event")
	FUNavigationTargetSlotOnAllocation OnAllocationDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Allocation|Event")
	FUNavigationTargetSlotOnChange OnAllocationChangeDelegate;


public:

	UFUNCTION(BlueprintNativeEvent)
	void OnAllocation(UNavigationTargetSlot* Slot);

	UFUNCTION(BlueprintNativeEvent)
	void OnUnallocation(UNavigationTargetSlot* Slot);
};
