// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWidget.generated.h"

class ULobbyPlayerSlotWidget;
class AServerPlayerState;
class UButton;
class UVerticalBox;
class UTextBlock;
/**
 * 
 */
UCLASS()
class TPPMULTI_API ULobbyWidget : public UUserWidget
{
	GENERATED_BODY()

private:

	UFUNCTION()
	void OnClicked_StartMatchButton();

	UFUNCTION()
	void OnClicked_ReadyButton();
	
	UFUNCTION()
	void OnClicked_CloseSessionButton();

	UFUNCTION()
	void OnServerPlayerChanged(const int32& InPlayerUID, AServerPlayerState* InServerPlayerState);

	UFUNCTION()
	void OnServerPlayerLogout(const int32& InPlayerUID);

	UFUNCTION()
	void OnPlayerReadyChanged(const bool InNewIsReady);

	UPROPERTY()
	TMap<int32, ULobbyPlayerSlotWidget*> PlayerSlots;

protected:

	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnStartTravelToMatchWorld();

#pragma region BindWidgets

private:

	UPROPERTY(meta=(BindWidget), BlueprintGetter = GetSessionNameBox)
	TObjectPtr<UTextBlock> SessionNameBox;

	UPROPERTY(meta=(BindWidget), BlueprintGetter = GetPlayerSlotsBox)
	TObjectPtr<UVerticalBox> PlayerSlotsBox;

	UPROPERTY(meta=(BindWidget), BlueprintGetter = GetStartMatchButton)
	TObjectPtr<UButton> StartMatchButton;

	UPROPERTY(meta=(BindWidget), BlueprintGetter = GetReadyButton)
	TObjectPtr<UButton> ReadyButton;

	UPROPERTY(meta=(BindWidget), BlueprintGetter = GetCloseSessionButton)
	TObjectPtr<UButton> CloseSessionButton;

public:

	UFUNCTION(BlueprintGetter)
	UTextBlock* GetSessionNameBox() const
	{
		return SessionNameBox;
	}

	UFUNCTION(BlueprintGetter)
	UVerticalBox* GetPlayerSlotsBox() const
	{
		return PlayerSlotsBox;
	}

	UFUNCTION(BlueprintGetter)
	UButton* GetStartMatchButton() const
	{
		return StartMatchButton;
	}

	UFUNCTION(BlueprintGetter)
	UButton* GetReadyButton() const
	{
		return ReadyButton;
	}

	UFUNCTION(BlueprintGetter)
	UButton* GetCloseSessionButton() const
	{
		return CloseSessionButton;
	}
	
#pragma endregion 
	
};
