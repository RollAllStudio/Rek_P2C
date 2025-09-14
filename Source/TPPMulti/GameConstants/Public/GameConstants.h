// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GameConstants.generated.h"

class ULobbyPlayerSlotWidget;
class USessionJoinSlotWidget;
class ULobbyWidget;
class UMainMenuWidget;
/**
 * 
 */
UCLASS(Config = Game, DefaultConfig, DisplayName = "Game constants")
class TPPMULTI_API UGameConstants : public UDeveloperSettings
{
	GENERATED_BODY()

	static const UGameConstants* Get();

#pragma region Match

private:
	
	UPROPERTY(EditAnywhere, Config, Category = "Match", DisplayName = "Lobby World", meta=(AllowedClasses="/Script/Engine.World"))
	FSoftObjectPath MatchWorldPath;

public:

	UFUNCTION(BlueprintPure, Category = "GameConstants|Match")
	static FSoftObjectPath GetMatchWorldPath();
	
#pragma endregion 
	
#pragma region UI

private:
	
	UPROPERTY(EditAnywhere, Config, Category = UI)
	TSubclassOf<UMainMenuWidget> MainMenuWidgetClass;

	UPROPERTY(EditAnywhere, Config, Category = UI)
	TSubclassOf<ULobbyWidget> LobbyWidgetClass;

	UPROPERTY(EditAnywhere, Config, Category = UI)
	TSubclassOf<USessionJoinSlotWidget> SessionJoinWidgetSlotClass;

	UPROPERTY(EditAnywhere, Config, Category = UI)
	TSubclassOf<ULobbyPlayerSlotWidget> LobbyPlayerWidgetSlotClass;	
	
public:

	UFUNCTION(BlueprintPure, Category = "GameConstants|UI")
	static TSubclassOf<UMainMenuWidget> GetMainMenuWidgetClass();

	UFUNCTION(BlueprintPure, Category = "GameConstants|UI")
	static TSubclassOf<ULobbyWidget> GetLobbyWidgetClass();

	UFUNCTION(BlueprintPure, Category = "GameConstants|UI")
	static TSubclassOf<USessionJoinSlotWidget> GetSessionJoinWidgetSlotClass();

	UFUNCTION(BlueprintPure, Category = "GameConstants|UI")
	static TSubclassOf<ULobbyPlayerSlotWidget> GetLobbyPlayerSlotWidgetClass();
	
#pragma endregion 
	
};
