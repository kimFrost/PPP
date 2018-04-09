// Fill out your copyright notice in the Description page of Project Settings.

#include "UNavigationTargetSlot.h"



UNavigationTargetSlot::UNavigationTargetSlot()
{
	AllowedAllocationClass = UObject::StaticClass();
}


UNavigationTargetSlot::~UNavigationTargetSlot()
{
	
}

void UNavigationTargetSlot::Allocate(UObject* Allocatable)
{
	if (Allocatable)
	{
		
	}
}

void UNavigationTargetSlot::Unallocate(UObject* Allocatable)
{
	if (Allocated)
	{
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