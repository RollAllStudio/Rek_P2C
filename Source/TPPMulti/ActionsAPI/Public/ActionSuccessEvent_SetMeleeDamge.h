// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/Config/ActionDefinitions/ActionSuccessEvent/Public/ActionSuccessEvent_Base.h"
#include "ActionSuccessEvent_SetMeleeDamge.generated.h"

/**
 * 
 */
UCLASS()
class TPPMULTI_API UActionSuccessEvent_SetMeleeDamge : public UActionSuccessEvent_Base
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float DamageToSet;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UDamageType> DamageType;

public:

	virtual void Execute(UActionsComponent* InActionsComponent) override;
	
};
