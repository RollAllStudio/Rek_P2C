// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MatchHUDWidget.generated.h"

class UTextBlock;
class UOverlay;
class UWidgetSwitcher;
/**
 * 
 */
UCLASS()
class TPPMULTI_API UMatchHUDWidget : public UUserWidget
{
	GENERATED_BODY()

	UFUNCTION()
	void OnPlayerWin(const int32& InPlayerUID);

protected:

	virtual void NativeOnInitialized() override;

#pragma region BindWidgets

private:

	UPROPERTY(meta=(BindWidget), BlueprintGetter = GetMainSwitcher)
	TObjectPtr<UWidgetSwitcher> MainSwitcher;

	UPROPERTY(meta=(BindWidget), BlueprintGetter = GetFinishedMatchOverlay)
	TObjectPtr<UOverlay> FinishedMatchOverlay;

	UPROPERTY(meta=(BindWidget), BlueprintGetter = GetWinnerNameBox)
	TObjectPtr<UTextBlock> WinnerNameBox;

	UPROPERTY(meta=(BindWidget), BlueprintGetter = GetMatchOverlay)
	TObjectPtr<UOverlay> MatchOverlay;
	
public:

	UFUNCTION(BlueprintGetter)
	UWidgetSwitcher* GetMainSwitcher() const
	{
		return MainSwitcher;
	}

	UFUNCTION(BlueprintGetter)
	UOverlay* GetFinishedMatchOverlay() const
	{
		return FinishedMatchOverlay;
	}

	UFUNCTION(BlueprintGetter)
	UTextBlock* GetWinnerNameBox() const
	{
		return WinnerNameBox;
	}

	UFUNCTION(BlueprintGetter)
	UOverlay* GetMatchOverlay()
	{
		return MatchOverlay;
	}
	
#pragma endregion 
	
};
