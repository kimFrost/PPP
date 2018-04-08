// Fill out your copyright notice in the Description page of Project Settings.

#include "UAllocatable.h"
#include "UObjects/UAllocationSlot.h"




UAllocatable::UAllocatable()
{
	ActorOwner = nullptr;
}


UAllocatable::~UAllocatable()
{
	
}

void UAllocatable::AllocateTo(UAllocationSlot* AllocationSlot)
{
	if (AllocationSlot)
	{
		//~~ All logic is happening in AllocationSlot ~~//
		AllocationSlot->Allocate(this);
	}
}

void UAllocatable::Unallocate()
{
	if (AllocatedTo)
	{
		//~~ All logic is happening in AllocationSlot ~~//
		AllocatedTo->Unallocate(this);
	}
}

void UAllocatable::OnAllocated_Implementation(UAllocatable* Allocatable)
{}
void UAllocatable::OnUnallocated_Implementation(UAllocatable* Allocatable)
{}