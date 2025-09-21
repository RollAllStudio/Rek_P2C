// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreboardSlotWidget.generated.h"

class UTextBlock;
class AMatchPlayerState;
/**
 * 
 */
UCLASS()
class TPPMULTI_API UScoreboardSlotWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(BlueprintSetter = SetPlayerState)
	AMatchPlayerState* PlayerState;

	UFUNCTION()
	void OnPlayerScoreChanged(const int InNewScore);

	UFUNCTION()
	void OnPlayerNameChanged(const FString& InNewName);

public:

	UFUNCTION(BlueprintSetter)
	void SetPlayerState(AMatchPlayerState* InPlayerState);

#pragma region BindWidgets

private:

	UPROPERTY(meta=(BindWidget), BlueprintGetter = GetPlayerNameTextBlock)
	TObjectPtr<UTextBlock> PlayerNameTextBlock;

	UPROPERTY(meta=(BindWidget), BlueprintGetter = GetPlayerScoreTextBlock)
	TObjectPtr<UTextBlock> PlayerScoreTextBlock;

public:

	UFUNCTION(BlueprintGetter)
	UTextBlock* GetPlayerNameTextBlock() const
	{
		return PlayerNameTextBlock;
	}

	UFUNCTION(BlueprintGetter)
	UTextBlock* GetPlayerScoreTextBlock() const
	{
		return PlayerScoreTextBlock;
	}
	
#pragma endregion 
	
};
