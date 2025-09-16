// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterSlotWidget.generated.h"

class UTextBlock;
class UImage;
class UButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCharacterSlotWidget_PreSelect_Signature);

UCLASS()
class TPPMULTI_API UCharacterSlotWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(BlueprintSetter = SetIsSelected)
	bool bIsSelected = true;

	UPROPERTY(BlueprintSetter = SetCharacterRow)
	FDataTableRowHandle CharacterRow;

protected:

	virtual void NativeOnInitialized() override;

public:

	UFUNCTION(BlueprintCallable)
	void Select();

	UFUNCTION(BlueprintSetter)
	void SetCharacterRow(const FDataTableRowHandle& InCharacterRow);

	UFUNCTION(BlueprintSetter)
	void SetIsSelected(const bool InIsSelected);
	
	UPROPERTY(BlueprintAssignable)
	FCharacterSlotWidget_PreSelect_Signature OnPreSelect;
	
#pragma region BindWidgets

private:
	
	UPROPERTY(meta=(BindWidget), BlueprintGetter = GetSelectButton)
	TObjectPtr<UButton> SelectButton;

	UPROPERTY(meta=(BindWidget), BlueprintGetter = GetCharacterImage)
	TObjectPtr<UImage> CharacterImage;

	UPROPERTY(meta=(BindWidget), BlueprintGetter = GetCharacterNameTextBlock)
	TObjectPtr<UTextBlock> CharacterNameTextBlock;

public:

	UFUNCTION(BlueprintGetter)
	UButton* GetSelectButton() const
	{
		return SelectButton;
	}

	UFUNCTION(BlueprintGetter)
	UImage* GetCharacterImage() const
	{
		return CharacterImage;
	}

	UFUNCTION(BlueprintGetter)
	UTextBlock* GetCharacterNameTextBlock() const
	{
		return CharacterNameTextBlock;
	}

#pragma endregion 
	
};
