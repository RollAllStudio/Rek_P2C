// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/Core/Gamemodes/Public/LobbyGameMode.h"
#include "MultiplayerGame/Server/Public/ServerPlayerController.h"
#include "TPPMulti/Core/GameStates/Public/LobbyGameState.h"
#include "TPPMulti/Core/PlayerStates/Public/LobbyPlayerState.h"
#include "TPPMulti/UI/HUD/Public/LobbyHUD.h"

ALobbyGameMode::ALobbyGameMode()
{
	HUDClass = ALobbyHUD::StaticClass();
	PlayerControllerClass = AServerPlayerController::StaticClass();
	PlayerStateClass = ALobbyPlayerState::StaticClass();
	GameStateClass = ALobbyGameState::StaticClass();
}
