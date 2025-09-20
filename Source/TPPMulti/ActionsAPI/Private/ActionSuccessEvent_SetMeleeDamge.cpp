// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/ActionsAPI/Public/ActionSuccessEvent_SetMeleeDamge.h"
#include "Actions/Runtime/Public/ActionsComponent.h"
#include "TPPMulti/MeleeDamageCollider/Public/MeleeDamageColliderComponent.h"

void UActionSuccessEvent_SetMeleeDamge::Execute(UActionsComponent* InActionsComponent)
{

	UMeleeDamageColliderComponent* DamageCollider =
		InActionsComponent->GetOwner()->GetComponentByClass<UMeleeDamageColliderComponent>();

	if (IsValid(DamageCollider))
	{
		DamageCollider->SetDamage(DamageToSet);
		DamageCollider->SetDamageType(DamageType);	
	}
}
