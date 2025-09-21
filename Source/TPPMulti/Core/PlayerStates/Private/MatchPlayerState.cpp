// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/Core/PlayerStates/Public/MatchPlayerState.h"

#include "MultiplayerGameSubsystem.h"
#include "Net/UnrealNetwork.h"
#include "TPPMulti/ServerPlayerData/Public/MyServerPlayerData.h"

void AMatchPlayerState::IncrementWins_Implementation()
{
	UMyServerPlayerData* ServerPlayerData = Cast<UMyServerPlayerData>(
		UMultiplayerGameSubsystem::GetServerPlayerData(this, GetServerUID()));
	ServerPlayerData->IncrementWins();
}

void AMatchPlayerState::ScorePlayer()
{
	PlayerScore ++;
}

void AMatchPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMatchPlayerState, PlayerScore)
}
