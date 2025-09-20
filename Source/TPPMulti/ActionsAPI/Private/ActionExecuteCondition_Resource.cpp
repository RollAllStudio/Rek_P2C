// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/ActionsAPI/Public/ActionExecuteCondition_Resource.h"

#include "ResourcesComponent.h"
#include "Actions/Runtime/Public/ActionsComponent.h"

bool UActionExecuteCondition_Resource::DoConditionPass(UActionsComponent* InActionComponent)
{
	const UResourcesComponent* ResourcesComponent =
		InActionComponent->GetOwner()->GetComponentByClass<UResourcesComponent>();

	if (IsValid(ResourcesComponent))
	{
		const float ResourceValue = ResourcesComponent->GetResourceValue(ResourceTag);
		return ResourceValue >= MinResourceValue;
	}
	
	return false;
}
