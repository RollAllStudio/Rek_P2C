// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WaitWidget.generated.h"

class UTextBlock;
class UCircularThrobber;
/**
 * 
 */
UCLASS()
class TPPMULTI_API UWaitWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget), BlueprintGetter = GetThrobber)
	TObjectPtr<UCircularThrobber> Throbber;

	UPROPERTY(meta=(BindWidget), BlueprintGetter = GetWaitTextBlock)
	TObjectPtr<UTextBlock> WaitTextBlock;

public:

	UFUNCTION(BlueprintGetter)
	UCircularThrobber* GetThrobber() const
	{
		return Throbber;
	}

	UFUNCTION(BlueprintGetter)
	UTextBlock* GetWaitTextBlock() const
	{
		return WaitTextBlock;
	}

	UFUNCTION(BlueprintCallable)
	void SetWaitText(const FText& InText);
	
};
