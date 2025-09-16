// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharactersListWidget.generated.h"

class AServerPlayerState;
class UCharacterSlotWidget;
class UHorizontalBox;
/**
 * 
 */
UCLASS()
class TPPMULTI_API UCharactersListWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UDataTable* CharactersDataTable;

	UPROPERTY(meta=(BindWidget), BlueprintGetter = GetSlotsBox)
	TObjectPtr<UHorizontalBox> SlotsBox;

	UFUNCTION()
	void OnServerPlayerChanged(const int32& InPlayerUID, AServerPlayerState* InPlayerState);

	UFUNCTION()
	void OnPreSelectSlot();

	UPROPERTY()
	TArray<UCharacterSlotWidget*> Slots;

public:

	UFUNCTION(BlueprintGetter)
	UHorizontalBox* GetSlotsBox() const
	{
		return SlotsBox;
	}

protected:

	virtual void NativeOnInitialized() override;
	
};
