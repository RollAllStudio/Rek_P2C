// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/Core/MatchPlayer/Public/MatchPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "TPPMulti/GameConstants/Public/GameConstants.h"

AMatchPlayerCharacter::AMatchPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraBoomComponent = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");

	CameraBoomComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->SetupAttachment(CameraBoomComponent);

	CameraBoomComponent->bUsePawnControlRotation = true;
	
}

void AMatchPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	UGameConstants::GetCharacterMeshRef().ToSoftObjectPath().LoadAsync(
		FLoadSoftObjectPathAsyncDelegate::CreateUObject(this, &AMatchPlayerCharacter::OnCharacterMeshLoaded));

	CameraBoomComponent->TargetArmLength = UGameConstants::GetCameraBoomLen();
	CameraBoomComponent->ProbeChannel = UGameConstants::GetCameraBoomProbeChannel();
	CameraBoomComponent->SetRelativeTransform(UGameConstants::GetCameraBoomOffset());
	
}

void AMatchPlayerCharacter::OnCharacterMeshLoaded(const FSoftObjectPath& InAssetPath, UObject* InAsset)
{
	GetMesh()->SetSkeletalMeshAsset(Cast<USkeletalMesh>(InAsset));
	GetMesh()->SetRelativeTransform(UGameConstants::GetCharacterTransformOffset());
	GetMesh()->SetAnimInstanceClass(UGameConstants::GetCharacterAnimInstance());
}
