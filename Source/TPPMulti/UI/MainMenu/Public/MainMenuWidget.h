// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UEditableTextBox;
class UVerticalBox;
class UButton;
/**
 * 
 */
UCLASS()
class TPPMULTI_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

private:

	UFUNCTION()
	void OnClicked_HostGameButton();

	UFUNCTION()
	void OnClicked_ExitGameButton();

	UFUNCTION()
	void OnTextChanged_SessionNameBox(const FText& InNewText);

	UFUNCTION()
	void OnTextCommitted_SessionNameBox(const FText& InNewText, ETextCommit::Type InCommitMethod);
	
protected:

	virtual void NativeOnInitialized() override;
	
#pragma region BindWidget

private:
	
	UPROPERTY(meta=(BindWidget), BlueprintGetter = GetSessionNameBox)
	TObjectPtr<UEditableTextBox> SessionNameBox;
	
	UPROPERTY(meta=(BindWidget), BlueprintGetter = GetHostGameButton)
	TObjectPtr<UButton> HostGameButton;

	UPROPERTY(meta=(BindWidget), BlueprintGetter = GetSessionsBox)
	TObjectPtr<UVerticalBox> SessionsBox;

	UPROPERTY(meta=(BindWidget), BlueprintGetter = GetExitGameButton)
	TObjectPtr<UButton> ExitGameButton;
	
public:

	UFUNCTION(BlueprintGetter)
	UEditableTextBox* GetSessionNameBox() const
	{
		return SessionNameBox;
	}

	UFUNCTION(BlueprintGetter)
	UButton* GetHostGameButton() const
	{
		return HostGameButton;
	}

	UFUNCTION(BlueprintGetter)
	UVerticalBox* GetSessionsBox() const
	{
		return SessionsBox;
	}

	UFUNCTION(BlueprintGetter)
	UButton* GetExitGameButton() const
	{
		return ExitGameButton;
	}

#pragma endregion 
	
};
