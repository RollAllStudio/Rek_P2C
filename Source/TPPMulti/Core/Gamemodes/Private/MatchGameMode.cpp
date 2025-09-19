// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/Core/Gamemodes/Public/MatchGameMode.h"

#include "MultiplayerGame/Server/Public/ServerGameState.h"
#include "MultiplayerGame/Server/Public/ServerPlayerState.h"
#include "TPPMulti/Core/MatchPlayer/Public/MatchPlayerCharacter.h"
#include "TPPMulti/Core/MatchPlayer/Public/MatchPlayerController.h"
#include "TPPMulti/UI/HUD/Public/MatchHUD.h"

AMatchGameMode::AMatchGameMode()
{
	PlayerControllerClass = AMatchPlayerController::StaticClass();
	DefaultPawnClass = AMatchPlayerCharacter::StaticClass();
	PlayerStateClass = AServerPlayerState::StaticClass();
	GameStateClass = AServerGameState::StaticClass();
	HUDClass = AMatchHUD::StaticClass();
}
