// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerGameConstants.h"

const UMultiplayerGameConstants* UMultiplayerGameConstants::Get()
{
	return GetDefault<UMultiplayerGameConstants>();
}

int UMultiplayerGameConstants::GetMaxSessionNameLen()
{
	return Get()->MaxSessionNameLen;
}

int UMultiplayerGameConstants::GetMasPlayerNameLen()
{
	return Get()->MaxPlayerNameLen;
}

int UMultiplayerGameConstants::GetMaxPublicConnections()
{
	return Get()->MaxPublicConnections;
}

int UMultiplayerGameConstants::GetMaxSessionsFind()
{
	return Get()->MaxSessionsFind;
}

FSoftObjectPath UMultiplayerGameConstants::GetLobbyWorldPath()
{
	return Get()->LobbyWorldPath;
}

FSoftObjectPath UMultiplayerGameConstants::GetSessionDestroyedReturnWorldPath()
{
	return Get()->SessionDestroyedReturnWorldPath;
}
