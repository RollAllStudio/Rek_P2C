// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionSuccessEvent_Base.h"
#include "ActionSuccessEvent_Composite.generated.h"

class UActionExecuteCondition_Base;
/**
 * 
 */
UCLASS(DisplayName = "Composite")
class ACTIONS_API UActionSuccessEvent_Composite : public UActionSuccessEvent_Base
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Instanced)
	TArray<TObjectPtr<UActionSuccessEvent_Base>> Elements;

public:

	virtual void Execute(UActionsComponent* InActionsComponent) override;
	
};
