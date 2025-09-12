// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SessionJoinSlotWidget.generated.h"

class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS()
class TPPMULTI_API USessionJoinSlotWidget : public UUserWidget
{
	GENERATED_BODY()

	UFUNCTION()
	void OnClicked_JoinSessionButton();

	UPROPERTY(BlueprintGetter = GetSessionIndex)
	int32 SessionIndex = INDEX_NONE;

public:

	void SetupSlot(const int32& InSearchIndex, const FOnlineSessionSearchResult& InSessionSearchResult);

	UFUNCTION(BlueprintGetter)
	int32 GetSessionIndex() const
	{
		return SessionIndex;
	}
	
protected:

	virtual void NativeOnInitialized() override;

#pragma region BindWidgets

private:
	
	UPROPERTY(meta=(BindWidget), BlueprintGetter = GetJoinSessionButton)
	TObjectPtr<UButton> JoinSessionButton;

	UPROPERTY(meta=(BindWidget), BlueprintGetter = GetSessionNameTextBlock)
	TObjectPtr<UTextBlock> SessionNameTextBlock;

	UPROPERTY(meta=(BindWidget), BlueprintGetter = GetPlayersAmountTextBlock)
	TObjectPtr<UTextBlock> PlayersAmountTextBlock;

	UPROPERTY(meta=(BindWidget), BlueprintGetter = GetPingTextBlock)
	TObjectPtr<UTextBlock> PingTextBlock;

public:

	UFUNCTION(BlueprintGetter)
	UButton* GetJoinSessionButton() const
	{
		return JoinSessionButton;
	}

	UFUNCTION(BlueprintGetter)
	UTextBlock* GetSessionNameTextBlock() const
	{
		return SessionNameTextBlock;
	}

	UFUNCTION(BlueprintGetter)
	UTextBlock* GetPlayersAmountTextBlock() const
	{
		return PlayersAmountTextBlock;
	}

	UFUNCTION(BlueprintGetter)
	UTextBlock* GetPingTextBlock() const
	{
		return PingTextBlock;
	}
	
#pragma endregion 
	
};
