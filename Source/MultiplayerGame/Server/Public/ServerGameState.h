// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ServerGameState.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERGAME_API AServerGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	
	UFUNCTION(NetMulticast, Reliable)
	void LogoutServerPlayer(const int32& InServerPlayerUID);
	
};
