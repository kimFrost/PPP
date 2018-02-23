// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/DataTable.h"
#include "UCustomTypesLibrary.generated.h"



UENUM(BlueprintType)
enum class EPersonMood : uint8
{
	VE_Neutral UMETA(DisplayName = "Neutral"),
	VE_Angry UMETA(DisplayName = "Angry")
};

/*
UENUM(BlueprintType)
namespace EPersonMood
{
	enum Type
	{
		Neutral,			
		Angry,		
	};
}
*/

UCLASS()
class PPP_API UCustomTypesLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
};


//https://forums.unrealengine.com/development-discussion/c-gameplay-programming/14115-how-to-create-c-enum-that-can-have-new-entries-added-in-blueprint