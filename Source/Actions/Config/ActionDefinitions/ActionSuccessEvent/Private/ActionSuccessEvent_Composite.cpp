// Fill out your copyright notice in the Description page of Project Settings.


#include "..\Public\ActionSuccessEvent_Composite.h"

void UActionSuccessEvent_Composite::Execute(UActionsComponent* InActionsComponent)
{
	for (auto Element : Elements)
	{
		if (IsValid(Element))
			Element.Get()->Execute(InActionsComponent);
	}
}
