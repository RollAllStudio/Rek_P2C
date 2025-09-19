// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerGame/Server/Public/ServerGameState.h"
#include "MultiplayerGameSubsystem.h"

void AServerGameState::LogoutServerPlayer_Implementation(const int32& InServerPlayerUID)
{
	UMultiplayerGameSubsystem::LogoutServerPlayer(this, InServerPlayerUID);
}