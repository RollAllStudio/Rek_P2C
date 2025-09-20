// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/Config/ActionExecuteCondition/Public/ActionExecuteCondition_Composite.h"


bool UActionExecuteCondition_Composite::DoConditionPass(UActionsComponent* InActionComponent)
{
	for (auto Element : Elements)
		if (IsValid(Element))
			if (!Element.Get()->DoConditionPass(InActionComponent))
				return false;

	return true;
}