// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "MultiplayerGame/Server/Public/ServerPlayerController.h"
#include "MatchPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TPPMULTI_API AMatchPlayerController : public AServerPlayerController
{
	GENERATED_BODY()

protected:
	
	virtual void OnPossess(APawn* InPawn) override;

private:
	
	UFUNCTION()
	void InputAction_Move_Triggered(const FInputActionValue& InInputValue);

	UFUNCTION()
	void InputAction_Camera_Triggered(const FInputActionValue& InInputValue);

	UFUNCTION()
	void InputAction_Jump_Triggered(const FInputActionValue& InInputValue);
	
};
