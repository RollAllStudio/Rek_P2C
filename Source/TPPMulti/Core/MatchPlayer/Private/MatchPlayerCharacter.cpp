// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/Core/MatchPlayer/Public/MatchPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
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

	GetMesh()->SetIsReplicated(true);
	GetCharacterMovement()->SetIsReplicated(true);
	
}

void AMatchPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	CameraBoomComponent->TargetArmLength = UGameConstants::GetCameraBoomLen();
	CameraBoomComponent->ProbeChannel = UGameConstants::GetCameraBoomProbeChannel();
	CameraBoomComponent->SetRelativeTransform(UGameConstants::GetCameraBoomOffset());
}

void AMatchPlayerCharacter::OnCharacterMeshLoaded(const FSoftObjectPath& InAssetPath, UObject* InAsset)
{
	GetMesh()->SetSkeletalMeshAsset(Cast<USkeletalMesh>(InAsset));
	GetMesh()->SetRelativeTransform(CharacterData.MeshOffset);
	GetMesh()->SetAnimInstanceClass(CharacterData.AnimInstance);
}

void AMatchPlayerCharacter::LoadCharacterData(const FDataTableRowHandle& InDataRow)
{
	if (UCharactersDataBase::ReadCharacterData(InDataRow, CharacterData))
	{
		CharacterData.Mesh.ToSoftObjectPath().LoadAsync(
			FLoadSoftObjectPathAsyncDelegate::CreateUObject(this, &AMatchPlayerCharacter::OnCharacterMeshLoaded));
	}
}
