// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/ServerPlayerData/Public/MyServerPlayerData.h"
#include "TPPMulti/Core/PlayerStates/Public/LobbyPlayerState.h"

void UMyServerPlayerData::InitByPlayerState(AServerPlayerState* InPlayerState)
{
#pragma region LobbyPS

	const ALobbyPlayerState* LobbyPlayerState = Cast<ALobbyPlayerState>(InPlayerState);
	if (IsValid(LobbyPlayerState))
		SetCharacterRow(LobbyPlayerState->GetCharacterRow());

#pragma endregion 
	
}

void UMyServerPlayerData::SetCharacterRow(const FDataTableRowHandle& InCharacterRow)
{
	CharacterRow = InCharacterRow;
}
