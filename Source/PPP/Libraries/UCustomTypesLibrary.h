// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/DataTable.h"
#include "UCustomTypesLibrary.generated.h"



//~~~~~ Forward Declarations ~~~~~//
class UStat;


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


USTRUCT(BlueprintType)
struct FST_Payload
{
	GENERATED_USTRUCT_BODY()
public:
	FST_Payload(
		TMap<FString, int32> Stats = TMap<FString, int32>(),
		TMap<FString, bool> States = TMap<FString, bool>(),
		TArray<FString> Items = TArray<FString>())
		: Stats(Stats)
		, States(States)
		, Items(Items)
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
	TMap<FString, int32> Stats;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
	TMap<FString, bool> States;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
	TArray<FString> Items;
};

/*
{
stats: [
{stress: -1},
{ money: -1 }
	   ],
	states : [
{drunk: true}
			 ],
	items : []
}
*/


/*** FST_Structure ***/
USTRUCT(BlueprintType)
struct FST_Structure : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FST_Structure(
		FString ID = "",
		FString Title = "",
		float Price = 0,
		int Colums = 1,
		int Rows = 1)
		: ID(ID)
		, Title(Title)
		, Price(Price)
		, Colums(Colums)
		, Rows(Rows)
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString Title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Price;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int Colums;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int Rows;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TSubclassOf<AActor> StructureClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Structure")
	TAssetPtr<UStaticMesh> PreviewMesh;
};


UCLASS()
class PPP_API UCustomTypesLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
};


//https://forums.unrealengine.com/development-discussion/c-gameplay-programming/14115-how-to-create-c-enum-that-can-have-new-entries-added-in-blueprint