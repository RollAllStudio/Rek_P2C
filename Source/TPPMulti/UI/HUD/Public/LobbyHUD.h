// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LobbyHUD.generated.h"

class ULobbyWidget;
/**
 * 
 */
UCLASS()
class TPPMULTI_API ALobbyHUD : public AHUD
{
	GENERATED_BODY()

	UPROPERTY()
	ULobbyWidget* LobbyWidget;

protected:

	virtual void BeginPlay() override;
	
};
