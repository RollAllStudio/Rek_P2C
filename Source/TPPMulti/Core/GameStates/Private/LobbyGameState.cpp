// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/Core/GameStates/Public/LobbyGameState.h"

#include "Net/UnrealNetwork.h"

void ALobbyGameState::NetMulticast_StartTravelToMatchWorld_Implementation()
{
	OnStartTravelToMatchWorld.Broadcast();
}

void ALobbyGameState::OnRep_WinConditionKills()
{
	OnWinConditionKillsChanged.Broadcast(WinConditionKills);
}

void ALobbyGameState::SetWinConditionKills(const int InValue)
{
	WinConditionKills = InValue;
}

void ALobbyGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ALobbyGameState, WinConditionKills);
}
