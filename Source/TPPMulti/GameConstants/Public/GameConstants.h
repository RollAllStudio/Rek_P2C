// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GameConstants.generated.h"

class UMainMenuWidget;
/**
 * 
 */
UCLASS(Config = Game, DefaultConfig, DisplayName = "Game constants")
class TPPMULTI_API UGameConstants : public UDeveloperSettings
{
	GENERATED_BODY()

	static const UGameConstants* Get();
	
#pragma region UI

private:
	
	UPROPERTY(EditAnywhere, Config, Category = UI)
	TSubclassOf<UMainMenuWidget> MainMenuWidgetClass;

public:

	UFUNCTION(BlueprintPure, Category = "GameConstants|UI")
	static TSubclassOf<UMainMenuWidget> GetMainMenuWidgetClass();

#pragma endregion 
	
};
