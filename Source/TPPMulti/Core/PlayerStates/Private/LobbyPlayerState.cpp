// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/Core/PlayerStates/Public/LobbyPlayerState.h"
#include "MultiplayerGameSubsystem.h"
#include "Net/UnrealNetwork.h"

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

void ALobbyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ALobbyPlayerState, bIsReady)
}
