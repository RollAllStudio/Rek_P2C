// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MultiplayerGame/Server/Public/ServerPlayerData.h"
#include "MyServerPlayerData.generated.h"

UCLASS()
class TPPMULTI_API UMyServerPlayerData : public UServerPlayerData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintGetter = GetCharacterRow, BlueprintSetter = SetCharacterRow)
	FDataTableRowHandle CharacterRow;

	UPROPERTY(BlueprintGetter = GetWins)
	int Wins;
	
public:
	
	virtual void InitByPlayerState(AServerPlayerState* InPlayerState) override;

	UFUNCTION(BlueprintGetter)
	FDataTableRowHandle GetCharacterRow() const
	{
		return CharacterRow;
	}

	UFUNCTION(BlueprintGetter)
	int GetWins() const
	{
		return Wins;
	}

	UFUNCTION(BlueprintCallable)
	void IncrementWins();

	UFUNCTION(BlueprintSetter)
	void SetCharacterRow(const FDataTableRowHandle& InCharacterRow);
	
};
