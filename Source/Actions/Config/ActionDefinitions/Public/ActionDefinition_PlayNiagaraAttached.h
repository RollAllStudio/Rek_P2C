// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionDefinition_Base.h"
#include "ActionDefinition_PlayNiagaraAttached.generated.h"

class UNiagaraSystem;
/**
 * 
 */
UCLASS()
class ACTIONS_API UActionDefinition_PlayNiagaraAttached : public UActionDefinition_Base
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* SystemToPlay;

	UPROPERTY(EditAnywhere)
	float LockStackTime = 1.0f;

protected:

	virtual float ExecuteAction_Internal(UActionsComponent* InActionsComponent) override;
	
};
