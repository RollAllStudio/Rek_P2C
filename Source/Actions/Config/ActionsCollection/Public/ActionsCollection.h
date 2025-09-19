// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "ActionsCollection.generated.h"

class UActionDefinition_Base;
/**
 * 
 */
UCLASS()
class ACTIONS_API UActionsCollection : public UDataAsset
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Instanced)
	TMap<FGameplayTag, TObjectPtr<UActionDefinition_Base>> Actions;

public:

	UFUNCTION(BlueprintCallable)
	bool FindActionByTag(const FGameplayTag& InActionTag, UActionDefinition_Base*& OutAction);
	
};
