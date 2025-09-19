// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/Config/ActionDefinitions/Public/ActionDefinition_Base.h"
#include "Actions/Runtime/Public/ActionsComponent.h"

float UActionDefinition_Base::ExecuteAction_Internal(UActionsComponent* InActionsComponent)
{
	return -1;
}

void UActionDefinition_Base::ExecuteAction(UActionsComponent* InActionsComponent)
{

	if (!InActionsComponent->IsStackLocked(ActionStack))
	{
		const float MainStackLockTime =
			ExecuteAction_Internal(InActionsComponent);
		InActionsComponent->LockStack(ActionStack, MainStackLockTime);

		for (auto StackLock : StackLocks)
			InActionsComponent->LockStack(StackLock.Key, StackLock.Value);
	}
}
