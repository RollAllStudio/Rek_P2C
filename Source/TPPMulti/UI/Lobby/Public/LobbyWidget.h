// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWidget.generated.h"

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
	void OnClicked_CloseSessionButton();

protected:

	virtual void NativeOnInitialized() override;

#pragma region BindWidgets

private:

	UPROPERTY(meta=(BindWidget), BlueprintGetter = GetSessionNameBox)
	TObjectPtr<UTextBlock> SessionNameBox;

	UPROPERTY(meta=(BindWidget), BlueprintGetter = GetPlayerSlotsBox)
	TObjectPtr<UVerticalBox> PlayerSlotsBox;

	UPROPERTY(meta=(BindWidget), BlueprintGetter = GetStartMatchButton)
	TObjectPtr<UButton> StartMatchButton;

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
	UButton* GetCloseSessionButton() const
	{
		return CloseSessionButton;
	}
	
#pragma endregion 
	
};
