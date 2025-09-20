// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Actions/Config/ActionExecuteCondition/Public/ActionExecuteCondition_Base.h"
#include "ActionExecuteCondition_Resource.generated.h"

/**
 * 
 */
UCLASS()
class TPPMULTI_API UActionExecuteCondition_Resource : public UActionExecuteCondition_Base
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FGameplayTag ResourceTag;

	UPROPERTY(EditAnywhere)
	float MinResourceValue;

public:

	virtual bool DoConditionPass(UActionsComponent* InActionComponent) override;
	
};
