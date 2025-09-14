// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerGame/Server/Public/ServerGameMode.h"
#include "MultiplayerGame/Server/Public/ServerGameState.h"
#include "MultiplayerGame/Server/Public/ServerPlayerController.h"

void AServerGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	Cast<AServerPlayerController>(NewPlayer)->Client_LoginServerPlayer();
}

void AServerGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	const AServerPlayerController* AsServerPlayerController =
		Cast<AServerPlayerController>(Exiting);

	AServerGameState* ServerGameState =	GetGameState<AServerGameState>();
	
	if (IsValid(AsServerPlayerController) && IsValid(ServerGameState))
		ServerGameState->LogoutServerPlayer(AsServerPlayerController->GetServerUID());
}
