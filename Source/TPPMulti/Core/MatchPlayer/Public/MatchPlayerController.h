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

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMatchPlayerController_VoidEvent_Signature);

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

	UPROPERTY(BlueprintAssignable)
	FMatchPlayerController_VoidEvent_Signature OnOpenScoreboardInput;

	UPROPERTY(BlueprintAssignable)
	FMatchPlayerController_VoidEvent_Signature OnCloseScoreboardInput;
	
protected:
	
	virtual void SetupInputComponent() override;
	virtual void SetPawn(APawn* InPawn) override;

private:

	bool bIsScoreboardShown = false;
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

	UFUNCTION()
	void InputAction_Scoreboard_Start(const FInputActionValue& InInputValue);

	UFUNCTION()
	void InputAction_Scoreboard_Complete(const FInputActionValue& InInputValue);

	UFUNCTION()
	void InputAction_LeaveSession_Triggered(const FInputActionValue& InInputValue);
	
};
