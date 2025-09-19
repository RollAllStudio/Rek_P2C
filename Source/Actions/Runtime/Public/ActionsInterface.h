// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "ActionsInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class ACTIONS_API UActionsInterface : public UInterface
{
	GENERATED_BODY()

public:

	static void TryExecuteAction(UObject* InObject, const FGameplayTag& InActionTag);
	
};

/**
 * 
 */
class ACTIONS_API IActionsInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent)
	void TryExecuteAction(const FGameplayTag& InActionTag);
	
};
