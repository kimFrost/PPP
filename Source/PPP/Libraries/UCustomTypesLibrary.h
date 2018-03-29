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

UENUM(BlueprintType)
enum class EPropertyTarget : uint8
{
	None UMETA(DisplayName = "None"),
	MovementSpeed UMETA(DisplayName = "MovementSpeed")
};



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

/*** FST_Effect ***/
USTRUCT(BlueprintType)
struct FST_Effect
{
	GENERATED_USTRUCT_BODY()
public:
	FST_Effect(
		EPropertyTarget Target = EPropertyTarget::None,
		float Value = 1.f)
		: Target(Target)
		, Value(Value)
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
	EPropertyTarget Target;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
	float Value;
};

/*** FST_PersonState ***/
USTRUCT(BlueprintType)
struct FST_PersonState : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FST_PersonState(
		FString ID = "",
		FString Title = "",
		TArray<FString> Categories = TArray<FString>(),
		TArray<FST_Effect> Effects = TArray<FST_Effect>())
		: ID(ID)
		, Title(Title)
		, Categories(Categories)
		, Effects(Effects)
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString Title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TArray<FString> Categories;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TArray<FST_Effect> Effects;
};

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
		int32 Colums = 1,
		int32 Rows = 1,
		FVector2D EntranceCoord = FVector2D(0, 0))
		: ID(ID)
		, Title(Title)
		, Price(Price)
		, Colums(Colums)
		, Rows(Rows)
		, EntranceCoord(EntranceCoord)
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString Title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Price;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Colums;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Rows;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FVector2D EntranceCoord;
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