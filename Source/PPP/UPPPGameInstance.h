// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Libraries/UCustomTypesLibrary.h"
#include "UPPPGameInstance.generated.h"


//~~~~~ Forward Declarations ~~~~~//
class UDataTable;



UCLASS()
class PPP_API UPPPGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPPPGameInstance();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	UDataTable* DATA_Structures;
	
private:

	void ReadTables();


public:

	FST_Structure* GetStructureRowData(FString RowName);

};
