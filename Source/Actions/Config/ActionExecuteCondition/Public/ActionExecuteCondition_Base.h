// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ActionExecuteCondition_Base.generated.h"

class UActionsComponent;
/**
 * 
 */
UCLASS(Abstract, EditInlineNew, DefaultToInstanced)
class ACTIONS_API UActionExecuteCondition_Base : public UObject
{
	GENERATED_BODY()

public:

	virtual bool DoConditionPass(UActionsComponent* InActionComponent);
	
};