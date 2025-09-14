// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/UI/Lobby/Public/LobbyPlayerSlotWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "TPPMulti/Core/PlayerStates/Public/LobbyPlayerState.h"

void ULobbyPlayerSlotWidget::OnPlayerNameChanged(const FString& InNewName)
{
	ServerNameTextBlock->SetText(FText::FromString(InNewName));
}

void ULobbyPlayerSlotWidget::OnPlayerReadyChanged(const bool InNewIsReady)
{
	ReadyImage->SetVisibility(InNewIsReady ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Hidden);
}

void ULobbyPlayerSlotWidget::UnbindPlayerState()
{
	if (IsValid(ServerPlayerState))
	{
		ServerPlayerState->OnServerUIDChanged.RemoveAll(this);
		ServerPlayerState->OnServerNameChanged.RemoveAll(this);
		ServerPlayerState->OnIsReadyChanged.RemoveAll(this);
	}
}

void ULobbyPlayerSlotWidget::SetPlayerState_Internal(ALobbyPlayerState* InPlayerState)
{
	UnbindPlayerState();
	ServerPlayerState = InPlayerState;
	if (IsValid(ServerPlayerState))
	{
		OnPlayerNameChanged(InPlayerState->GetServerPlayerName());
		InPlayerState->OnServerNameChanged.AddUniqueDynamic(this, &ULobbyPlayerSlotWidget::OnPlayerNameChanged);
		OnPlayerReadyChanged(InPlayerState->GetIsReady());
		InPlayerState->OnIsReadyChanged.AddUniqueDynamic(this, &ULobbyPlayerSlotWidget::OnPlayerReadyChanged);
	}
}

void ULobbyPlayerSlotWidget::SetPlayerState(ALobbyPlayerState* InPlayerState)
{
	if (InPlayerState != ServerPlayerState)
		SetPlayerState_Internal(InPlayerState);
}
