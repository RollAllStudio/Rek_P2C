// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_SpawnSpellProjectile.generated.h"

class USpellConfig;
/**
 * 
 */
UCLASS(DisplayName = "Spawn spell projectile")
class TPPMULTI_API UAnimNotify_SpawnSpellProjectile : public UAnimNotify
{
	GENERATED_BODY()

public:

	UAnimNotify_SpawnSpellProjectile();

private:
	
	UPROPERTY(EditAnywhere)
	USpellConfig* SpellConfig = nullptr;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
};
