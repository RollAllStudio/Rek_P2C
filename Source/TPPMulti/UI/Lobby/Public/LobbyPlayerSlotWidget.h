// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyPlayerSlotWidget.generated.h"

class UImage;
class ALobbyPlayerState;
class UTextBlock;
/**
 * 
 */
UCLASS()
class TPPMULTI_API ULobbyPlayerSlotWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(BlueprintGetter = GetPlayerState, BlueprintSetter = SetPlayerState)
	ALobbyPlayerState* ServerPlayerState;

	UFUNCTION()
	void OnPlayerNameChanged(const FString& InNewName);

	UFUNCTION()
	void OnPlayerReadyChanged(const bool InNewIsReady);
	
	void UnbindPlayerState();
	void SetPlayerState_Internal(ALobbyPlayerState* InPlayerState);
	
public:

	UFUNCTION(BlueprintGetter)
	ALobbyPlayerState* GetPlayerState() const
	{
		return ServerPlayerState;
	}
	
	UFUNCTION(BlueprintSetter)
	void SetPlayerState(ALobbyPlayerState* InPlayerState);

#pragma region BindWidgets

private:

	UPROPERTY(meta=(BindWidget), BlueprintGetter = GetServerNameTextBlock)
	TObjectPtr<UTextBlock> ServerNameTextBlock;

	UPROPERTY(meta=(BindWidget), BlueprintGetter = GetReadyImage)
	TObjectPtr<UImage> ReadyImage;

public:
	

	UFUNCTION(BlueprintGetter)
	UTextBlock* GetServerNameTextBlock() const
	{
		return ServerNameTextBlock;
	}

	UFUNCTION(BlueprintGetter)
	UImage* GetReadyImage() const
	{
		return ReadyImage;
	}
	
#pragma endregion 
	
};
