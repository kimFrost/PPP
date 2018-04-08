// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UAllocationSlot.generated.h"


//~~~~~ Forward Declarations ~~~~~//
class UAllocationSlot;
class AActor;


//~~~~~ Deleagtes ~~~~~//
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUAllocationSlotOnUnallocation, UAllocationSlot*, AllocationSlot, AActor*, Allocatable);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUAllocationSlotOnAllocation, UAllocationSlot*, AllocationSlot, AActor*, Allocatable);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUAllocationSlotOnChange, UAllocationSlot*, AllocationSlot, AActor*, Allocatable);
//DECLARE_DELEGATE_RetVal(UAllocatable*, FRequestAllocatable);

//DECLARE_DELEGATE_RetVal_TwoParams(UAllocatable*, FRequestAllocatable, TSubclassOf<class UAllocatable>, FString);
DECLARE_DELEGATE_RetVal_TwoParams(AActor*, FRequestAllocatable, UClass*, FString);


UCLASS(Blueprintable, BlueprintType)
class PPP_API UAllocationSlot : public UObject
{
	GENERATED_BODY()

public:
	UAllocationSlot();
	~UAllocationSlot();

	//TSubclassOf<class UAllocatable> AllowedAllocationClass;
	UClass* AllowedAllocationClass;
	FString AllowedAllocationID;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AActor* ActorOwner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Allocation")
	UObject* Allocated;

	UObject* PrevAllocated;

public:

	UFUNCTION(BlueprintCallable, Category = "Allocation")
	void Allocate(UObject* Allocatable);
	
	UFUNCTION(BlueprintCallable, Category = "Allocation")
	void Unallocate(UObject* Allocatable = nullptr);

	UFUNCTION(BlueprintCallable, Category = "Allocation")
	void Toggle();

	UFUNCTION(BlueprintCallable, Category = "Allocation")
	void RequestAllocation();

public:

	FRequestAllocatable OnRequestAllocatable;

	UPROPERTY(BlueprintAssignable, Category = "Allocation|Event")
	FUAllocationSlotOnUnallocation OnUnallocationDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Allocation|Event")
	FUAllocationSlotOnAllocation OnAllocationDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Allocation|Event")
	FUAllocationSlotOnChange OnAllocationChangeDelegate;


public:

	UFUNCTION(BlueprintNativeEvent)
	void OnAllocation(UAllocationSlot* Slot);

	UFUNCTION(BlueprintNativeEvent)
	void OnUnallocation(UAllocationSlot* Slot);
};
