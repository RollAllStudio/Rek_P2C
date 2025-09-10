// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "MultiplayerGameConstants.generated.h"

/**
 * 
 */
UCLASS(Config = Game, DefaultConfig, DisplayName = "Multiplayer Game Constants")
class MULTIPLAYERGAME_API UMultiplayerGameConstants : public UDeveloperSettings
{
	GENERATED_BODY()

private:

	static const UMultiplayerGameConstants* Get();

	UPROPERTY(EditAnywhere, Config)
	int MaxSessionNameLen = 25;

	UPROPERTY(EditAnywhere, Config)
	int MaxPublicConnections = 2;

	UPROPERTY(EditAnywhere, Config, DisplayName = "Lobby World", meta=(AllowedClasses="/Script/Engine.World"))
	FSoftObjectPath LobbyWorldPath;

	UPROPERTY(EditAnywhere, Config, DisplayName = "Session destroyed return World", meta=(AllowedClasses="/Script/Engine.World"))
	FSoftObjectPath SessionDestroyedReturnWorldPath;

public:

	UFUNCTION(BlueprintPure, Category = "GameConstants|Multiplayer")
	static int GetMaxSessionNameLen();

	UFUNCTION(BlueprintPure, Category = "GameConstants|Multiplayer")
	static int GetMaxPublicConnections();

	UFUNCTION(BlueprintPure, Category = "GameConstants|Multiplayer")
	static FSoftObjectPath GetLobbyWorldPath();

	UFUNCTION(BlueprintPure, Category = "GameConstants|Multiplayer")
	static FSoftObjectPath GetSessionDestroyedReturnWorldPath();
	
};
