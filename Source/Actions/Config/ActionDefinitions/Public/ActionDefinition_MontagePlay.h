// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionDefinition_Base.h"
#include "ActionDefinition_MontagePlay.generated.h"

/**
 *	Action to play montage in character.
 *	Can be executed only from ACharacter or childs
 */
UCLASS(DisplayName = "Play montage")
class ACTIONS_API UActionDefinition_MontagePlay : public UActionDefinition_Base
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UAnimMontage* MontageToPlay;

	UPROPERTY(EditAnywhere)
	float PlayRate = 1.0f;

	UFUNCTION()
	TArray<FName> GetSelectedMontageSections() const;

protected:

	virtual float ExecuteAction_Internal(UActionsComponent* InActionsComponent) override;

};
