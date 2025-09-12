// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SessionsBrowserWidget.generated.h"

class USessionsFindResult;
class UVerticalBox;
/**
 * 
 */
UCLASS()
class TPPMULTI_API USessionsBrowserWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget), BlueprintGetter = GetSessionsBox)
	TObjectPtr<UVerticalBox> SessionsBox;

public:

	UFUNCTION(BlueprintGetter)
	UVerticalBox* GetSessionsBox() const
	{
		return SessionsBox;
	}

protected:

	virtual void NativeOnInitialized() override;
	virtual void NativeDestruct() override;

private:

	UFUNCTION()
	void OnSessionsSearchComplete(USessionsFindResult* InFindResult);
	
};
