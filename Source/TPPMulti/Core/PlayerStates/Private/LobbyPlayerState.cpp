// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/Core/PlayerStates/Public/LobbyPlayerState.h"
#include "MultiplayerGameSubsystem.h"
#include "Net/UnrealNetwork.h"
#include "TPPMulti/ServerPlayerData/Public/MyServerPlayerData.h"

void ALobbyPlayerState::Server_SetIsReady_Implementation(const bool InNewIsReady)
{
	SetIsReadyInternal(InNewIsReady);
}

bool ALobbyPlayerState::Server_SetIsReady_Validate(const bool InNewIsReady)
{
	return UMultiplayerGameSubsystem::IsHost(this);
}

void ALobbyPlayerState::OnRep_IsReady()
{
	SetIsReadyInternal(bIsReady);
}

void ALobbyPlayerState::SetIsReadyInternal(const bool InNewIsReady)
{
	bIsReady = InNewIsReady;
	OnIsReadyChanged.Broadcast(bIsReady);
}

void ALobbyPlayerState::SetIsReady(const bool InNewIsReady)
{
	if (bIsReady != InNewIsReady)
		Server_SetIsReady(InNewIsReady);
}

void ALobbyPlayerState::OnRep_CharacterRow()
{
	SetCharacterRow_Internal(CharacterRow);
}

void ALobbyPlayerState::SetCharacterRow_Internal(const FDataTableRowHandle& InCharacterRow)
{
	CharacterRow = InCharacterRow;

	UMyServerPlayerData* ServerPlayerData =
		Cast<UMyServerPlayerData>(UMultiplayerGameSubsystem::GetServerPlayerData(this, GetServerUID()));

	if (IsValid(ServerPlayerData))
		ServerPlayerData->SetCharacterRow(CharacterRow);
	
	OnCharacterRowChanged.Broadcast(CharacterRow);
}

void ALobbyPlayerState::Server_SetCharacterRow_Implementation(const FDataTableRowHandle& InCharacterRow)
{
	SetCharacterRow(InCharacterRow);
}

bool ALobbyPlayerState::Server_SetCharacterRow_Validate(const FDataTableRowHandle& InCharacterRow)
{
	return UMultiplayerGameSubsystem::IsHost(this);
}

void ALobbyPlayerState::SetCharacterRow(const FDataTableRowHandle& InCharacterRow)
{
	if (InCharacterRow != CharacterRow)
	{
		if (!UMultiplayerGameSubsystem::IsHost(this))
			Server_SetCharacterRow(InCharacterRow);

		SetCharacterRow_Internal(InCharacterRow);
	}
}

void ALobbyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ALobbyPlayerState, bIsReady)
	DOREPLIFETIME_CONDITION(ALobbyPlayerState, CharacterRow, COND_SkipOwner)
}
