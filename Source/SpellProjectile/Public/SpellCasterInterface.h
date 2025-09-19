// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SpellCasterInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class USpellCasterInterface : public UInterface
{
	GENERATED_BODY()

public:

	static FTransform GetSpellInitialTransform(UObject* InObject);
	static APawn* GetSpellInstigatorPawn(UObject* InObject);

};

/**
 * 
 */
class SPELLPROJECTILE_API ISpellCasterInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent)
	FTransform GetSpellInitialTransform();

	UFUNCTION(BlueprintNativeEvent)
	APawn* GetSpellInstigatorPawn();
	
};
