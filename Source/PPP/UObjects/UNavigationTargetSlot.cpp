// Fill out your copyright notice in the Description page of Project Settings.

#include "UNavigationTargetSlot.h"
#include "AActors/AStructure.h"



UNavigationTargetSlot::UNavigationTargetSlot()
{
	AllowedAllocationClass = AStructure::StaticClass();
}


UNavigationTargetSlot::~UNavigationTargetSlot()
{
	
}

void UNavigationTargetSlot::Allocate(AStructure* Structure)
{
	if (Structure)
	{
		Allocated = Structure;
		OnAllocationDelegate.Broadcast(this, Allocated);
		OnAllocationChangeDelegate.Broadcast(this, Allocated);
		OnAllocation(this);

		/*
		Allocatable->Unallocate();

		//Allocatable->Allocate(this); // Need to call allocate on resource without going into infinity mode

		Allocated = Allocatable;
		Allocated->AllocatedTo = this;

		Allocated->OnUnallocatedDelegate.AddUniqueDynamic(this, &UAllocationSlot::Unallocate);

		Allocated->OnAllocatedDelegate.Broadcast(Allocated);
		Allocated->OnAllocated(Allocated);

		OnAllocationChangeDelegate.Broadcast(this, Allocated);
		OnAllocation(this);
		*/
	}
}

void UNavigationTargetSlot::Unallocate(AStructure* Structure)
{
	if (Allocated)
	{
		PrevAllocated = Allocated;
		Allocated = nullptr;

		OnUnallocationDelegate.Broadcast(this, PrevAllocated);
		OnAllocationChangeDelegate.Broadcast(this, PrevAllocated);
		OnUnallocation(this);

		/*
		Allocated->OnUnallocatedDelegate.RemoveDynamic(this, &UNavigationTargetSlot::Unallocate);

		Allocated->AllocatedTo = nullptr;
		PrevAllocated = Allocated;
		Allocated = nullptr;

		PrevAllocated->OnUnallocatedDelegate.Broadcast(PrevAllocated);
		PrevAllocated->OnUnallocated(PrevAllocated);

		OnUnallocationDelegate.Broadcast(this, PrevAllocated);
		OnAllocationChangeDelegate.Broadcast(this, PrevAllocated);
		OnUnallocation(this);
		*/
	}
}

void UNavigationTargetSlot::OnAllocation_Implementation(UNavigationTargetSlot* Slot)
{}
void UNavigationTargetSlot::OnUnallocation_Implementation(UNavigationTargetSlot* Slot)
{}