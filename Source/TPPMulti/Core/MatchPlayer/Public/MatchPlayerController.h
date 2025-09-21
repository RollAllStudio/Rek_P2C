// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "MultiplayerGame/Server/Public/ServerPlayerController.h"
#include "MatchPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMatchPlayerController_OnPlayerWin_Signature,
	const int32&, PlayerUID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMatchPlayerController_OnNewPawnSet_Signature,
	APawn*, NewPawn);

UCLASS()
class TPPMULTI_API AMatchPlayerController : public AServerPlayerController
{
	GENERATED_BODY()

public:

	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_OnPlayerWin(const int32& InPlayerUID);

	UPROPERTY(BlueprintAssignable)
	FMatchPlayerController_OnPlayerWin_Signature OnPlayerWin;

	UPROPERTY(BlueprintAssignable)
	FMatchPlayerController_OnNewPawnSet_Signature OnNewPawnSet_Signature;
	
protected:
	
	virtual void SetupInputComponent() override;
	virtual void SetPawn(APawn* InPawn) override;

private:

	bool bMatchFinished = false;
	bool CanControlPawn() const;
	
	UFUNCTION()
	void InputAction_Move_Triggered(const FInputActionValue& InInputValue);

	UFUNCTION()
	void InputAction_Camera_Triggered(const FInputActionValue& InInputValue);

	UFUNCTION()
	void InputAction_Jump_Triggered(const FInputActionValue& InInputValue);

	UFUNCTION()
	void InputAction_PrimaryAction_Triggered(const FInputActionValue& InInputValue);
	
};
