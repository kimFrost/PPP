// Fill out your copyright notice in the Description page of Project Settings.

#include "UPPPGameInstance.h"
#include "Runtime/Engine/Classes/Engine/DataTable.h"
#include "Libraries/UCustomTypesLibrary.h"



UPPPGameInstance::UPPPGameInstance()
{
	ReadTables();
}

void UPPPGameInstance::ReadTables()
{
	UDataTable* StructureTable = (UDataTable*)StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("DataTable'/Game/PPP/Data/DATA_Structures.DATA_Structures'"));
	if (StructureTable)
	{
		DATA_Structures = StructureTable;
		/*
		TArray<FName> RowNames;
		RowNames = DATA_Structures->GetRowNames();
		for (auto& Name : RowNames)
		{
			CachedStructureIds.Add(Name.ToString());
		}
		*/
	}
	UDataTable* PersonStatesTable = (UDataTable*)StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("DataTable'/Game/PPP/Data/DATA_PersonStates.DATA_PersonStates'"));
	if (PersonStatesTable)
	{
		DATA_PersonStates = PersonStatesTable;
	}
}

FST_Structure* UPPPGameInstance::GetStructureRowData(FString RowName)
{
	if (DATA_Structures)
	{
		static const FString ContextString(TEXT("GENERAL")); //~~ Key value for each column of values ~~//
		return DATA_Structures->FindRow<FST_Structure>(*RowName, ContextString);
	}
	return nullptr;
}

FST_PersonState* UPPPGameInstance::GetPersonStateRowData(FString RowName)
{
	if (DATA_PersonStates)
	{
		static const FString ContextString(TEXT("GENERAL")); //~~ Key value for each column of values ~~//
		return DATA_PersonStates->FindRow<FST_PersonState>(*RowName, ContextString);
	}
	return nullptr;
}
