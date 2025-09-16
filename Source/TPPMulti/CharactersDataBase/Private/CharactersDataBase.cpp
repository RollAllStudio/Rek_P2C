// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/CharactersDataBase/Public/CharactersDataBase.h"

bool UCharactersDataBase::ReadCharacterData(const FDataTableRowHandle& InRowHandle, FCharacterData& OutData)
{
	if (InRowHandle.DataTable)
	{
		const TArray<FName> Rows = InRowHandle.DataTable->GetRowNames();
		if (Rows.Contains(InRowHandle.RowName))
		{
			OutData = *InRowHandle.DataTable->FindRow<FCharacterData>(InRowHandle.RowName,
				"Read character data");
			return true;
		}
	}

	return false;
}
