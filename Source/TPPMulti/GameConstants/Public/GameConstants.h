// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DeveloperSettings.h"
#include "GameConstants.generated.h"

class UMatchHUDWidget;
class UCharacterSlotWidget;
class UInputAction;
class UInputMappingContext;
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

#pragma region Camera

private:

	UPROPERTY(EditAnywhere, Config, Category = "Camera")
	float CameraBoomLen = 250.0f;

	UPROPERTY(EditAnywhere, Config, Category = "Camera")
	FTransform CameraBoomOffset;

	UPROPERTY(EditAnywhere, Config, Category = "Camera")
	TEnumAsByte<ECollisionChannel> CameraBoomProbeChannel;

public:

	UFUNCTION(BlueprintPure, Category = "GameConstants|Camera")
	static float GetCameraBoomLen();

	UFUNCTION(BlueprintPure, Category = "GameConstants|Camera")
	static FTransform GetCameraBoomOffset();

	UFUNCTION(BlueprintPure, Category = "GameConstants|Camera")
	static TEnumAsByte<ECollisionChannel> GetCameraBoomProbeChannel();
	
#pragma endregion 

#pragma region Input

private:

	UPROPERTY(EditAnywhere, Config, Category = "Input")
	TSoftObjectPtr<UInputMappingContext> DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, Config, Category = "Input")
	TMap<FGameplayTag, TSoftObjectPtr<UInputAction>> InputActions;

	UPROPERTY(EditAnywhere, Config, Category = "Input")
	FVector2D CameraPitchLimit = FVector2D(-45, 45);
	
public:

	// As input assets are loaded on game ini, they can be loaded synchronous
	
	UFUNCTION(BlueprintPure, Category = "GameConstants|Input")
	static UInputMappingContext* LoadDefaultInputMappingContext();

	UFUNCTION(BlueprintPure, Category = "GameConstants|Input")
	static bool LoadInputMappingByTag(const FGameplayTag& InActionTag, UInputAction*& OutInputAction);
	
	UFUNCTION(BlueprintPure, Category = "GameConstants|Input")
	static FVector2D GetCameraPitchLimit();	
	
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

	UPROPERTY(EditAnywhere, Config, Category = UI)
	TSubclassOf<UCharacterSlotWidget> CharacterSlotWidgetClass;

	UPROPERTY(EditAnywhere, Config, Category = UI)
	TSubclassOf<UMatchHUDWidget> MatchPlayerHUDWidgetClass;
	
public:

	UFUNCTION(BlueprintPure, Category = "GameConstants|UI")
	static TSubclassOf<UMainMenuWidget> GetMainMenuWidgetClass();

	UFUNCTION(BlueprintPure, Category = "GameConstants|UI")
	static TSubclassOf<ULobbyWidget> GetLobbyWidgetClass();

	UFUNCTION(BlueprintPure, Category = "GameConstants|UI")
	static TSubclassOf<USessionJoinSlotWidget> GetSessionJoinWidgetSlotClass();

	UFUNCTION(BlueprintPure, Category = "GameConstants|UI")
	static TSubclassOf<ULobbyPlayerSlotWidget> GetLobbyPlayerSlotWidgetClass();

	UFUNCTION(BlueprintPure, Category = "GameConstants|UI")
	static TSubclassOf<UCharacterSlotWidget> GetCharacterSlotWidgetClass();	

	UFUNCTION(BlueprintPure, Category = "GameConstants|UI")
	static TSubclassOf<UMatchHUDWidget> GetMatchHUDWidgetClass();
	
#pragma endregion 
	
};
