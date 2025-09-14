// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MultiplayerGame/Server/Public/ServerGameState.h"
#include "LobbyGameState.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLobbyGameState_OnStartTravelToMatchWorld_Signature);

UCLASS()
class TPPMULTI_API ALobbyGameState : public AServerGameState
{
	GENERATED_BODY()

public:
	
	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_StartTravelToMatchWorld();

	UPROPERTY(BlueprintAssignable)
	FLobbyGameState_OnStartTravelToMatchWorld_Signature OnStartTravelToMatchWorld;
	
};
