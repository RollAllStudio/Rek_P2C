// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_ToggleDamageCollider.generated.h"

/**
 * 
 */
UCLASS(DisplayName = "Toggle damage collider")
class TPPMULTI_API UAnimNotify_EnableDamageCollider : public UAnimNotify
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	bool bEnableDamage;
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
		const FAnimNotifyEventReference& EventReference) override;
	
};
