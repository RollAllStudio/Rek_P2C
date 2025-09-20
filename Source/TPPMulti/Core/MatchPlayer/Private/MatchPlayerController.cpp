// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/Core/MatchPlayer/Public/MatchPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Actions/Runtime/Public/ActionsInterface.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "TPPMulti/ActionsAPI/Public/ActionsTags.h"
#include "TPPMulti/GameConstants/Public/GameConstants.h"
#include "TPPMulti/InputTags/Public/InputTags.h"


void AMatchPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (IsLocalController())
	{
		UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem
	= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

		EnhancedInputSubsystem->ClearAllMappings();
		EnhancedInputSubsystem->AddMappingContext(UGameConstants::LoadDefaultInputMappingContext(), 0);

		UEnhancedInputComponent* LocalInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

#define BIND_ACTION(ActionRefVar, ActionTag, InputComp, EventType, Function) \
UInputAction* ActionRefVar; if (UGameConstants::LoadInputMappingByTag( InputTags:: ActionTag , ActionRefVar)) \
InputComp -> BindAction( ActionRefVar,  ETriggerEvent:: EventType, this, &AMatchPlayerController:: Function );

		BIND_ACTION(MoveActionConfig, Input_Move, LocalInputComponent, Triggered, InputAction_Move_Triggered)
		BIND_ACTION(CameraActionConfig, Input_Camera, LocalInputComponent, Triggered, InputAction_Camera_Triggered)
		BIND_ACTION(JumpActionConfig, Input_Jump, LocalInputComponent, Triggered, InputAction_Jump_Triggered)
		BIND_ACTION(PrimaryActionConfig, Input_PrimaryAction, LocalInputComponent,
			Triggered, InputAction_PrimaryAction_Triggered)
	
	#undef BIND_ACTION
	}
	
}

void AMatchPlayerController::InputAction_Move_Triggered(const FInputActionValue& InInputValue)
{
	FVector RawValue = InInputValue.Get<FVector>();
	const FRotator PawnRotation = GetPawn()->GetActorRotation();
	RawValue = PawnRotation.RotateVector(RawValue);
	GetPawn()->GetMovementComponent()->AddInputVector(RawValue);
}

void AMatchPlayerController::InputAction_Camera_Triggered(const FInputActionValue& InInputValue)
{
	const FVector RawValue = InInputValue.Get<FVector>();
	FRotator CurrentControlRotation = GetControlRotation();
	CurrentControlRotation.Yaw += RawValue.X;
	const FVector2D CameraPitchLimit = UGameConstants::GetCameraPitchLimit();
	CurrentControlRotation.Pitch = FMath::Clamp(
		CurrentControlRotation.Pitch + RawValue.Y, CameraPitchLimit.X, CameraPitchLimit.Y);
	SetControlRotation(CurrentControlRotation);
}

void AMatchPlayerController::InputAction_Jump_Triggered(const FInputActionValue& InInputValue)
{
	ACharacter* LocalCharacter = Cast<ACharacter>(GetPawn());
	LocalCharacter->Jump();
}

void AMatchPlayerController::InputAction_PrimaryAction_Triggered(const FInputActionValue& InInputValue)
{
	UActionsInterface::TryExecuteAction(GetPawn(), ActionTags::PrimaryAction);
}
