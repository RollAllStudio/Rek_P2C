// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/GameConstants/Public/GameConstants.h"
#include "InputMappingContext.h"
#include "InputAction.h"

const UGameConstants* UGameConstants::Get()
{
	return GetDefault<UGameConstants>();
}

FSoftObjectPath UGameConstants::GetMatchWorldPath()
{
	return Get()->MatchWorldPath;
}

TSoftObjectPtr<USkeletalMesh> UGameConstants::GetCharacterMeshRef()
{
	return Get()->CharacterMesh;
}

FTransform UGameConstants::GetCharacterTransformOffset()
{
	return Get()->CharacterTransformOffset;
}

TSubclassOf<UAnimInstance> UGameConstants::GetCharacterAnimInstance()
{
	return Get()->CharacterAnimInstance;
}

float UGameConstants::GetCameraBoomLen()
{
	return Get()->CameraBoomLen;
}

FTransform UGameConstants::GetCameraBoomOffset()
{
	return Get()->CameraBoomOffset;
}

TEnumAsByte<ECollisionChannel> UGameConstants::GetCameraBoomProbeChannel()
{
	return Get()->CameraBoomProbeChannel;
}

UInputMappingContext* UGameConstants::LoadDefaultInputMappingContext()
{
	return Get()->DefaultMappingContext.LoadSynchronous();
}

bool UGameConstants::LoadInputMappingByTag(const FGameplayTag& InActionTag, UInputAction*& OutInputAction)
{

	const UGameConstants* ConfigObject = Get();
	if (ConfigObject->InputActions.Contains(InActionTag))
	{
		OutInputAction = ConfigObject->InputActions[InActionTag].LoadSynchronous();
		return IsValid(OutInputAction);
	}
	return false;
}

FVector2D UGameConstants::GetCameraPitchLimit()
{
	return Get()->CameraPitchLimit;
}

TSubclassOf<UMainMenuWidget> UGameConstants::GetMainMenuWidgetClass()
{
	return Get()->MainMenuWidgetClass;
}

TSubclassOf<ULobbyWidget> UGameConstants::GetLobbyWidgetClass()
{
	return Get()->LobbyWidgetClass;
}

TSubclassOf<USessionJoinSlotWidget> UGameConstants::GetSessionJoinWidgetSlotClass()
{
	return Get()->SessionJoinWidgetSlotClass;
}

TSubclassOf<ULobbyPlayerSlotWidget> UGameConstants::GetLobbyPlayerSlotWidgetClass()
{
	return Get()->LobbyPlayerWidgetSlotClass;
}
