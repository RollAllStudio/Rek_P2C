// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerGame/Server/Public/ServerPlayerState.h"

#include "MultiplayerGameSubsystem.h"
#include "Net/UnrealNetwork.h"

void AServerPlayerState::OnRep_ServerPlayerName()
{
	SetServerPlayerName_Internal(ServerPlayerName);
}

void AServerPlayerState::OnRep_ServerUID()
{
	SetServerUID_Internal(ServerUID);
}

void AServerPlayerState::Server_ShareServerName_Implementation(const FString& InServerName)
{
	SetServerPlayerName_Internal(InServerName);
}

bool AServerPlayerState::Server_ShareServerName_Validate(const FString& InServerName)
{
	return UMultiplayerGameSubsystem::IsHost(this);
}

void AServerPlayerState::Server_ShareServerUID_Implementation(const int32& InServerUID)
{
	SetServerUID_Internal(InServerUID);
}

bool AServerPlayerState::Server_ShareServerUID_Validate(const int32& InServerUID)
{
	return UMultiplayerGameSubsystem::IsHost(this);
}

void AServerPlayerState::SetServerPlayerName_Internal(const FString& InNewName)
{
	ServerPlayerName = InNewName;
	OnServerNameChanged.Broadcast(ServerPlayerName);
	if (!UMultiplayerGameSubsystem::IsHost(this))
		Server_ShareServerName(InNewName);
}

void AServerPlayerState::SetServerUID_Internal(const int32& InNewUID)
{
	ServerUID = InNewUID;
	OnServerUIDChanged.Broadcast(ServerUID);
	UMultiplayerGameSubsystem::SetServerPlayerState(this, ServerUID, this);
	if (!UMultiplayerGameSubsystem::IsHost(this))
		Server_ShareServerUID(InNewUID);
}

void AServerPlayerState::SetServerPlayerName(const FString& InNewName)
{
	if (!ServerPlayerName.Equals(InNewName))
		SetServerPlayerName_Internal(InNewName);
}

void AServerPlayerState::SetServerUID(const int32& InServerUID)
{
	if (ServerUID != InServerUID)
		SetServerUID_Internal(InServerUID);
}

void AServerPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(AServerPlayerState, ServerUID, COND_SkipOwner)
	DOREPLIFETIME_CONDITION(AServerPlayerState, ServerPlayerName, COND_SkipOwner)
}
