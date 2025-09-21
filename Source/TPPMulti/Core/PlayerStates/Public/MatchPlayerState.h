// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MultiplayerGame/Server/Public/ServerPlayerState.h"
#include "MatchPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMatchPlayerState_OnScoreChanged_Signature, const int, NewScore);

UCLASS()
class TPPMULTI_API AMatchPlayerState : public AServerPlayerState
{
	GENERATED_BODY()

	UPROPERTY(ReplicatedUsing = OnRep_PlayerScore, BlueprintGetter = GetPlayerScore)
	int PlayerScore;

	UFUNCTION()
	void OnRep_PlayerScore();
	
public:

	UPROPERTY(BlueprintAssignable)
	FMatchPlayerState_OnScoreChanged_Signature OnPlayerScoreChanged;

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