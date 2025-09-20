// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Actions/Config/ActionDefinitions/ActionSuccessEvent/Public/ActionSuccessEvent_Base.h"
#include "ActionSuccessEvent_ConsumeResource.generated.h"

/**
 * 
 */
UCLASS()
class TPPMULTI_API UActionSuccessEvent_ConsumeResource : public UActionSuccessEvent_Base
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FGameplayTag ResourceTag;
	
	UPROPERTY(EditAnywhere)
	float ValueToConsume;

public:

	virtual void Execute(UActionsComponent* InActionsComponent) override;
	
};
