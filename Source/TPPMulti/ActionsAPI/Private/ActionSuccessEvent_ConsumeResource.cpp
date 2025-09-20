// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/ActionsAPI/Public/ActionSuccessEvent_ConsumeResource.h"

#include "ResourcesComponent.h"
#include "Actions/Runtime/Public/ActionsComponent.h"

void UActionSuccessEvent_ConsumeResource::Execute(UActionsComponent* InActionsComponent)
{
	UResourcesComponent* ResourcesComponent =
		InActionsComponent->GetOwner()->GetComponentByClass<UResourcesComponent>();

	if (IsValid(ResourcesComponent))
		ResourcesComponent->ConsumeResource(ResourceTag, ValueToConsume);
}
