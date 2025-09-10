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

int UMultiplayerGameConstants::GetMaxPublicConnections()
{
	return Get()->MaxPublicConnections;
}

FSoftObjectPath UMultiplayerGameConstants::GetLobbyWorldPath()
{
	return Get()->LobbyWorldPath;
}
