// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/ServerPlayerData/Public/MyServerPlayerData.h"

#include "MultiplayerGameSubsystem.h"
#include "TPPMulti/Core/PlayerStates/Public/LobbyPlayerState.h"

void UMyServerPlayerData::InitData(UMultiplayerGameSubsystem* MultiplayerGameSubsystem, const int32& InPlayerUID)
{
	Super::InitData(MultiplayerGameSubsystem, InPlayerUID);
	ALobbyPlayerState* LobbyPlayerState =
		Cast<ALobbyPlayerState>(UMultiplayerGameSubsystem::GetServerPlayerState(MultiplayerGameSubsystem,
			InPlayerUID));
	if (IsValid(LobbyPlayerState))
		SetCharacterRow(LobbyPlayerState->GetCharacterRow());
}

void UMyServerPlayerData::SetCharacterRow(const FDataTableRowHandle& InCharacterRow)
{
	CharacterRow = InCharacterRow;
}
