// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MultiplayerGame/Server/Public/ServerGameMode.h"
#include "MatchGameMode.generated.h"

class AMatchPlayerState;
/**
 * 
 */
UCLASS()
class TPPMULTI_API AMatchGameMode : public AServerGameMode
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<AActor*> PlayerStartActors;

	UFUNCTION()
	void FinishMatch(const int32& InWinnerUID);

	UFUNCTION()
	void TravelToLobby();

	UPROPERTY()
	FTimerHandle PostFinishMatchTimer;

protected:

	virtual void BeginPlay() override;
	
public:

	AMatchGameMode();

	UFUNCTION(BlueprintCallable)
	FVector GetRandomRespawnPosition() const;

	UFUNCTION(BlueprintCallable)
	void ScorePlayer(AMatchPlayerState* InPlayerState);
	
};
