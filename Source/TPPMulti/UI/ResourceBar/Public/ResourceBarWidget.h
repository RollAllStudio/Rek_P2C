// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"
#include "ResourceBarWidget.generated.h"

class UTextBlock;
class UProgressBar;
class UResourceInstance;
/**
 * 
 */
UCLASS()
class TPPMULTI_API UResourceBarWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintGetter = GetResourceTag)
	FGameplayTag ResourceTag;

	UPROPERTY(EditAnywhere)
	FLinearColor FillColorAndOpacity;

	UPROPERTY(BlueprintSetter = SetResourceInstance)
	UResourceInstance* ResourceInstance;

	void SetResourceInstance_Internal(UResourceInstance* InResourceInstance);
	void UnbindResourceInstance();

	UFUNCTION()
	void OnResourceChanged(const FGameplayTag& InResourceTag, UResourceInstance* InResourceInstance,
		const float InOldValue, const float InNewValue);
	
public:

	UFUNCTION(BlueprintGetter)
	FGameplayTag GetResourceTag() const
	{
		return ResourceTag;
	}
	
	UFUNCTION(BlueprintSetter)
	void SetResourceInstance(UResourceInstance* InResourceInstance);

protected:

	virtual void NativeOnInitialized() override;

#pragma region BindWidgets

private:

	UPROPERTY(meta=(BindWidget), BlueprintGetter = GetProgressBar)
	TObjectPtr<UProgressBar> ProgressBar;

	UPROPERTY(meta=(BindWidget), BlueprintGetter = GetCurrentValueTextBlock)
	TObjectPtr<UTextBlock> CurrentValueTextBlock;

public:

	UFUNCTION(BlueprintGetter)
	UProgressBar* GetProgressBar() const
	{
		return ProgressBar;
	}

	UFUNCTION(BlueprintGetter)
	UTextBlock* GetCurrentValueTextBlock() const
	{
		return CurrentValueTextBlock;
	}
	
#pragma endregion 
	
};
