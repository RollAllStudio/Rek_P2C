// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/Config/ActionDefinitions/Public/ActionDefinition_PlayNiagaraAttached.h"

#include "NiagaraFunctionLibrary.h"
#include "Actions/Runtime/Public/ActionsComponent.h"

float UActionDefinition_PlayNiagaraAttached::ExecuteAction_Internal(UActionsComponent* InActionsComponent)
{
	UNiagaraFunctionLibrary::SpawnSystemAttached(SystemToPlay, InActionsComponent->GetOwner()->GetRootComponent(),
		NAME_None, FVector(), FRotator(), EAttachLocation::SnapToTarget,true);
	
	return 1.0f;
}
