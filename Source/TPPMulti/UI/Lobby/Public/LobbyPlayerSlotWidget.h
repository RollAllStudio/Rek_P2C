// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyPlayerSlotWidget.generated.h"

class UTextBlock;
class AServerPlayerState;
/**
 * 
 */
UCLASS()
class TPPMULTI_API ULobbyPlayerSlotWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(BlueprintGetter = GetPlayerState, BlueprintSetter = SetPlayerState)
	AServerPlayerState* ServerPlayerState;

	UFUNCTION()
	void OnPlayerUIDChanged(const int32& InNewUID);

	UFUNCTION()
	void OnPlayerNameChanged(const FString& InNewName);
	
	void UnbindPlayerState();
	void SetPlayerState_Internal(AServerPlayerState* InPlayerState);
	
public:

	UFUNCTION(BlueprintGetter)
	AServerPlayerState* GetPlayerState() const
	{
		return ServerPlayerState;
	}
	
	UFUNCTION(BlueprintSetter)
	void SetPlayerState(AServerPlayerState* InPlayerState);

#pragma region BindWidgets

private:
	
	UPROPERTY(meta=(BindWidget), BlueprintGetter = GetServerUIDTextBlock)
	TObjectPtr<UTextBlock> ServerUIDTextBlock;

	UPROPERTY(meta=(BindWidget), BlueprintGetter = GetServerNameTextBlock)
	TObjectPtr<UTextBlock> ServerNameTextBlock;

public:

	UFUNCTION(BlueprintGetter)
	UTextBlock* GetServerUIDTextBlock() const
	{
		return ServerUIDTextBlock;
	}

	UFUNCTION(BlueprintGetter)
	UTextBlock* GetServerNameTextBlock() const
	{
		return ServerNameTextBlock;
	}
	
#pragma endregion 
	
};
