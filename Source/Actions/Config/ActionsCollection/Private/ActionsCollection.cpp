// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/Config/ActionsCollection/Public/ActionsCollection.h"
#include "Actions/Config/ActionDefinitions/Public/ActionDefinition_Base.h"

bool UActionsCollection::FindActionByTag(const FGameplayTag& InActionTag, UActionDefinition_Base*& OutAction)
{
	if (Actions.Contains(InActionTag))
	{
		OutAction = Actions[InActionTag];
		return IsValid(OutAction);
	}

	return false;
}
