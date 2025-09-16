// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ServerPlayerData.generated.h"

class UMultiplayerGameSubsystem;
class AServerPlayerState;
/**
 * 
 */
UCLASS()
class MULTIPLAYERGAME_API UServerPlayerData : public UObject
{
	GENERATED_BODY()

public:

	virtual void InitData(UMultiplayerGameSubsystem* MultiplayerGameSubsystem, const int32& InPlayerUID);
	
};
