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
UCLASS(Abstract, BlueprintType, Blueprintable)
class MULTIPLAYERGAME_API UServerPlayerData : public UObject
{
	GENERATED_BODY()

public:

	virtual void InitByPlayerState(AServerPlayerState* InPlayerState) PURE_VIRTUAL();
	
};
