// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MultiplayerGame/Server/Public/ServerGameState.h"
#include "LobbyGameState.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLobbyGameState_OnStartTravelToMatchWorld_Signature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLobbyGameState_OnWinConditionKillsChanged_Signature, const int, Value);

UCLASS()
class TPPMULTI_API ALobbyGameState : public AServerGameState
{
	GENERATED_BODY()

	UPROPERTY(ReplicatedUsing = OnRep_WinConditionKills, BlueprintGetter = GetWinConditionKills, BlueprintSetter = SetWinConditionKills)
	int WinConditionKills;

	UFUNCTION()
	void OnRep_WinConditionKills();

public:

	UPROPERTY(BlueprintAssignable)
	FLobbyGameState_OnWinConditionKillsChanged_Signature OnWinConditionKillsChanged;

	UFUNCTION(BlueprintGetter)
	int GetWinConditionKills() const
	{
		return WinConditionKills;
	}

	UFUNCTION(BlueprintSetter)
	void SetWinConditionKills(const int InValue);
	
	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_StartTravelToMatchWorld();

	UPROPERTY(BlueprintAssignable)
	FLobbyGameState_OnStartTravelToMatchWorld_Signature OnStartTravelToMatchWorld;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
};
