// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MultiplayerGame/Server/Public/ServerPlayerState.h"
#include "MatchPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class TPPMULTI_API AMatchPlayerState : public AServerPlayerState
{
	GENERATED_BODY()

	UPROPERTY(Replicated, BlueprintGetter = GetPlayerScore)
	int PlayerScore;

public:

	UFUNCTION(BlueprintCallable)
	void ScorePlayer();

	UFUNCTION(BlueprintGetter)
	int GetPlayerScore() const
	{
		return PlayerScore;
	}

	UFUNCTION(NetMulticast, Reliable)
	void IncrementWins();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
};