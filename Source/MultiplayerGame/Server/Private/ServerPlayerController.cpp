// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerGame/Server/Public/ServerPlayerController.h"
#include "MultiplayerGameSubsystem.h"
#include "MultiplayerGame/Server/Public/ServerPlayerState.h"
#include "Net/UnrealNetwork.h"

void AServerPlayerController::Client_LoginServerPlayer_Implementation()
{
	Server_LoginServerPlayer(UMultiplayerGameSubsystem::GetLocalPlayerUID(this));	
}

void AServerPlayerController::Server_LoginServerPlayer_Implementation(const int32& InServerPlayerUID)
{
	if (InServerPlayerUID == INDEX_NONE)
	{
		SetServerUID_Internal(UMultiplayerGameSubsystem::LoginNewPlayer(this));
		return;
	}

	SetServerUID_Internal(InServerPlayerUID);
	UMultiplayerGameSubsystem::LoginServerPlayerAtUID(this, InServerPlayerUID);
}

bool AServerPlayerController::Server_LoginServerPlayer_Validate(const int32& InServerPlayerUID)
{
	return UMultiplayerGameSubsystem::IsHost(this);
}

void AServerPlayerController::OnRep_ServerUID()
{
	SetServerUID_Internal(ServerUID);
}

void AServerPlayerController::SetServerUID_Internal(const int32& InNewUID)
{
	ServerUID = InNewUID;
	
	if (IsLocalController())
		UMultiplayerGameSubsystem::SetLocalPlayerUID(this, InNewUID);

	SetupServerPlayerState();
}

void AServerPlayerController::SetupServerPlayerState() const
{

	int32 LocalUID = UMultiplayerGameSubsystem::GetLocalPlayerUID(this);
	FString bHasPlayerState = IsValid(GetServerPlayerState()) ?
		"true" : "false";
	
	if (ServerUID != INDEX_NONE
		&& ServerUID == UMultiplayerGameSubsystem::GetLocalPlayerUID(this)
		&& IsValid(GetServerPlayerState()))
	{
		GetServerPlayerState()->SetServerUID(ServerUID);
		GetServerPlayerState()->SetServerPlayerName(
			UMultiplayerGameSubsystem::GetLocalPlayerName(this).ToString());
	}
}

void AServerPlayerController::InitPlayerState()
{
	Super::InitPlayerState();
	if (!UMultiplayerGameSubsystem::IsHost(this))
		SetupServerPlayerState();
}

void AServerPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	if (IsLocalController())
		SetupServerPlayerState();
}

AServerPlayerState* AServerPlayerController::GetServerPlayerState() const
{
	return Cast<AServerPlayerState>(PlayerState);
}

void AServerPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(AServerPlayerController, ServerUID, COND_OwnerOnly)
}
