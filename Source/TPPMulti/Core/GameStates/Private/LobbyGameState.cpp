// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/Core/GameStates/Public/LobbyGameState.h"

void ALobbyGameState::NetMulticast_StartTravelToMatchWorld_Implementation()
{
	OnStartTravelToMatchWorld.Broadcast();
}
