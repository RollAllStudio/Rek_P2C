// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/Core/MatchPlayer/Public/MatchPlayerCharacter.h"

#include "MultiplayerGameSubsystem.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "MultiplayerGame/Server/Public/ServerPlayerState.h"
#include "TPPMulti/GameConstants/Public/GameConstants.h"
#include "TPPMulti/ServerPlayerData/Public/MyServerPlayerData.h"

void AMatchPlayerCharacter::OnServerUIDChanged(const int32& InNewUID)
{
	InitWithPlayerState();
}

void AMatchPlayerCharacter::InitWithPlayerState()
{
	AServerPlayerState* ServerPlayerState = Cast<AServerPlayerState>(GetPlayerState());
	if (IsValid(ServerPlayerState))
	{
		ServerPlayerState->OnServerUIDChanged.RemoveAll(this);
		const int32 ServerUID = ServerPlayerState->GetServerUID();
		if (ServerUID != INDEX_NONE)
		{
			UMyServerPlayerData* MyServerPlayerData =
				Cast<UMyServerPlayerData>(UMultiplayerGameSubsystem::GetServerPlayerData(this, ServerUID));
			if (IsValid(MyServerPlayerData))
			{
				LoadCharacterData(MyServerPlayerData->GetCharacterRow());
			}
		}
		else
		{
			ServerPlayerState->OnServerUIDChanged.AddUniqueDynamic(this, &AMatchPlayerCharacter::OnServerUIDChanged);
		}
	}
}

AMatchPlayerCharacter::AMatchPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraBoomComponent = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");

	CameraBoomComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->SetupAttachment(CameraBoomComponent);

	CameraBoomComponent->bUsePawnControlRotation = true;
	
	bReplicates = true;
}

void AMatchPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	CameraBoomComponent->TargetArmLength = UGameConstants::GetCameraBoomLen();
	CameraBoomComponent->ProbeChannel = UGameConstants::GetCameraBoomProbeChannel();
	CameraBoomComponent->SetRelativeTransform(UGameConstants::GetCameraBoomOffset());
}

void AMatchPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
}

void AMatchPlayerCharacter::OnPlayerStateChanged(APlayerState* NewPlayerState, APlayerState* OldPlayerState)
{
	Super::OnPlayerStateChanged(NewPlayerState, OldPlayerState);
	InitWithPlayerState();
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
