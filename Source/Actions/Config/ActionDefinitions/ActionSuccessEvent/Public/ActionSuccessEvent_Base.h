// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ActionSuccessEvent_Base.generated.h"

class UActionsComponent;
/**
 * 
 */
UCLASS(DefaultToInstanced, EditInlineNew, Abstract)
class ACTIONS_API UActionSuccessEvent_Base : public UObject
{
	GENERATED_BODY()

public:

	virtual void Execute(UActionsComponent* InActionsComponent) PURE_VIRTUAL()
	
};
