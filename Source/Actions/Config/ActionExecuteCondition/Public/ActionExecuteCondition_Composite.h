// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionExecuteCondition_Base.h"
#include "ActionExecuteCondition_Composite.generated.h"

/**
 * 
 */
UCLASS(DisplayName = "Composite")
class ACTIONS_API UActionExecuteCondition_Composite : public UActionExecuteCondition_Base
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Instanced)
	TArray<TObjectPtr<UActionExecuteCondition_Base>> Elements;

public:

	virtual bool DoConditionPass(UActionsComponent* InActionComponent) override;
	
};
