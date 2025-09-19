// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/Runtime/Public/ActionsInterface.h"

void UActionsInterface::TryExecuteAction(UObject* InObject, const FGameplayTag& InActionTag)
{
	if (IsValid(InObject))
		if (InObject->Implements<UActionsInterface>())
			IActionsInterface::Execute_TryExecuteAction(InObject, InActionTag);
}
