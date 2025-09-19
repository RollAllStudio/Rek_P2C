// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellCasterInterface.h"


// Add default functionality here for any ISpellCasterInterface functions that are not pure virtual.
FTransform USpellCasterInterface::GetSpellInitialTransform(UObject* InObject)
{

	if (IsValid(InObject))
		if (InObject->Implements<USpellCasterInterface>())
			return ISpellCasterInterface::Execute_GetSpellInitialTransform(InObject);

	const AActor* AsActor = Cast<AActor>(InObject);
	if (IsValid(AsActor))
		return AsActor->GetTransform();

	const USceneComponent* AsSceneComp = Cast<USceneComponent>(InObject);
	if (IsValid(AsSceneComp))
		return AsSceneComp->GetComponentTransform();

	return FTransform();
}

APawn* USpellCasterInterface::GetSpellInstigatorPawn(UObject* InObject)
{
	if (IsValid(InObject))
		if (InObject->Implements<USpellCasterInterface>())
			return ISpellCasterInterface::Execute_GetSpellInstigatorPawn(InObject);

	return nullptr;
}
