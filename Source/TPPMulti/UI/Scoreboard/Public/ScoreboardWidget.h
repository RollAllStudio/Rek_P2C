// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreboardWidget.generated.h"

class AMatchPlayerState;
class AServerPlayerState;
class UVerticalBox;
/**
 * 
 */
UCLASS()
class TPPMULTI_API UScoreboardWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget), BlueprintGetter = GetSlotsBox)
	TObjectPtr<UVerticalBox> SlotsBox;

	UFUNCTION()
	void OnServerPlayerChanged(const int32& UID, AServerPlayerState* PlayerState);

	void RefreshPlayersList();
	void CreatePlayerSlot(AMatchPlayerState* InPlayerState);

protected:

	virtual void NativeOnInitialized() override;
	
public:

	UFUNCTION(BlueprintGetter)
	UVerticalBox* GetSlotsBox() const
	{
		return SlotsBox;
	}
	
};
