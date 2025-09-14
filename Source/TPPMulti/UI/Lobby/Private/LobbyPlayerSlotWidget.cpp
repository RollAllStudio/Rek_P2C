// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/UI/Lobby/Public/LobbyPlayerSlotWidget.h"

#include "Components/TextBlock.h"
#include "MultiplayerGame/Server/Public/ServerPlayerState.h"

void ULobbyPlayerSlotWidget::OnPlayerUIDChanged(const int32& InNewUID)
{
	ServerUIDTextBlock->SetText(FText::FromString(FString::FromInt(InNewUID)));
}

void ULobbyPlayerSlotWidget::OnPlayerNameChanged(const FString& InNewName)
{
	ServerNameTextBlock->SetText(FText::FromString(InNewName));
}

void ULobbyPlayerSlotWidget::UnbindPlayerState()
{
	if (IsValid(ServerPlayerState))
	{
		ServerPlayerState->OnServerUIDChanged.RemoveAll(this);
		ServerPlayerState->OnServerNameChanged.RemoveAll(this);
	}
}

void ULobbyPlayerSlotWidget::SetPlayerState_Internal(AServerPlayerState* InPlayerState)
{
	UnbindPlayerState();
	ServerPlayerState = InPlayerState;
	if (IsValid(ServerPlayerState))
	{
		OnPlayerUIDChanged(InPlayerState->GetServerUID());
		OnPlayerNameChanged(InPlayerState->GetServerPlayerName());

		InPlayerState->OnServerNameChanged.AddUniqueDynamic(this, &ULobbyPlayerSlotWidget::OnPlayerNameChanged);
		InPlayerState->OnServerUIDChanged.AddUniqueDynamic(this, &ULobbyPlayerSlotWidget::OnPlayerUIDChanged);
	}
}

void ULobbyPlayerSlotWidget::SetPlayerState(AServerPlayerState* InPlayerState)
{
	if (InPlayerState != ServerPlayerState)
		SetPlayerState_Internal(InPlayerState);
}
