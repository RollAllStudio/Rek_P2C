// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "ActionDefinition_Base.generated.h"

class UActionsComponent;
/**
 * 
 */
UCLASS(DefaultToInstanced, EditInlineNew, Abstract)
class ACTIONS_API UActionDefinition_Base : public UObject
{
	GENERATED_BODY()

	/*
	 * This action will lock this stack by default.
	 * This stack need to be unlocked to Execute this action.
	 */
	UPROPERTY(EditAnywhere)
	FGameplayTag ActionStack;

	/*
	 * Additional stack locks.
	 * This action will lock those stacks for specified duration.
	 * If lock here is set to value that is <= 0 then stack will
	 * not be unlocked by time.
	 */
	UPROPERTY(EditAnywhere)
	TMap<FGameplayTag, float> StackLocks;

protected:

	virtual float ExecuteAction_Internal(UActionsComponent* InActionsComponent);
	
public:

	void ExecuteAction(UActionsComponent* InActionsComponent);
	
};
