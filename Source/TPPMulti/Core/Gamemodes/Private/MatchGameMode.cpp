// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/Core/Gamemodes/Public/MatchGameMode.h"

#include "TPPMulti/Core/MatchPlayer/Public/MatchPlayerCharacter.h"
#include "TPPMulti/Core/MatchPlayer/Public/MatchPlayerController.h"

AMatchGameMode::AMatchGameMode()
{
	PlayerControllerClass = AMatchPlayerController::StaticClass();
	DefaultPawnClass = AMatchPlayerCharacter::StaticClass();
}
