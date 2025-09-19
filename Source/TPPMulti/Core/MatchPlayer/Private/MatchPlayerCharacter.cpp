// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/Core/MatchPlayer/Public/MatchPlayerCharacter.h"

#include "MultiplayerGameSubsystem.h"
#include "NativeGameplayTags.h"
#include "Actions/Runtime/Public/ActionsComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "DynamicMeshSpawner/Runtime/Public/DynamicMeshSpawnerComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "MultiplayerGame/Server/Public/ServerPlayerState.h"
#include "TPPMulti/GameConstants/Public/GameConstants.h"
#include "TPPMulti/ServerPlayerData/Public/MyServerPlayerData.h"

UE_DEFINE_GAMEPLAY_TAG_STATIC(MeshComponentTag, "DynamicComponents.Parent.CharacterMesh")
UE_DEFINE_GAMEPLAY_TAG_STATIC(WeaponComponentTag, "DynamicComponents.Weapon")

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

	CameraBoomComponent->SetupAttachment(GetRootComponent());
	CameraComponent->SetupAttachment(CameraBoomComponent);

	CameraBoomComponent->bUsePawnControlRotation = true;

	MeshRootComponent = CreateDefaultSubobject<USceneComponent>("Mesh root");
	MeshRootComponent->SetupAttachment(GetRootComponent());
	GetMesh()->SetupAttachment(MeshRootComponent);

	ActionsComponent = CreateDefaultSubobject<UActionsComponent>("ActionsComponent");
	DynamicMeshSpawnerComponent = CreateDefaultSubobject<UDynamicMeshSpawnerComponent>("DynamicMeshSpawner");
	
	bReplicates = true;
}

void AMatchPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	CameraBoomComponent->TargetArmLength = UGameConstants::GetCameraBoomLen();
	CameraBoomComponent->ProbeChannel = UGameConstants::GetCameraBoomProbeChannel();
	CameraBoomComponent->SetRelativeTransform(UGameConstants::GetCameraBoomOffset());
	SetReplicateMovement(true);
}

void AMatchPlayerCharacter::OnPlayerStateChanged(APlayerState* NewPlayerState, APlayerState* OldPlayerState)
{
	Super::OnPlayerStateChanged(NewPlayerState, OldPlayerState);
	InitWithPlayerState();
}

void AMatchPlayerCharacter::OnCharacterMeshLoaded(const FSoftObjectPath& InAssetPath, UObject* InAsset)
{
	GetMesh()->SetSkeletalMeshAsset(Cast<USkeletalMesh>(InAsset));
	MeshRootComponent->SetRelativeTransform(CharacterData.MeshOffset);
	GetMesh()->SetAnimInstanceClass(CharacterData.AnimInstance);
}

void AMatchPlayerCharacter::LoadCharacterData(const FDataTableRowHandle& InDataRow)
{
	if (UCharactersDataBase::ReadCharacterData(InDataRow, CharacterData))
	{
		// Load Character Mesh
		CharacterData.Mesh.ToSoftObjectPath().LoadAsync(
			FLoadSoftObjectPathAsyncDelegate::CreateUObject(this, &AMatchPlayerCharacter::OnCharacterMeshLoaded));

		// Load actions
		ActionsComponent->LoadActionsCollection(CharacterData.ActionsCollection);

		// Load dynamic meshes
		DynamicMeshSpawnerComponent->AddTaggedParent(MeshComponentTag, GetMesh());
		for (auto DynamicMeshData : CharacterData.DynamicMeshes)
			DynamicMeshSpawnerComponent->LoadAndSpawnMesh(DynamicMeshData.Key, DynamicMeshData.Value);
	}
}

void AMatchPlayerCharacter::Server_TryExecuteAction_Implementation(const FGameplayTag& InActionTag)
{
	ActionsComponent->TryExecuteAction(InActionTag);
	NetMulticast_TryExecuteAction(InActionTag);
}

bool AMatchPlayerCharacter::Server_TryExecuteAction_Validate(const FGameplayTag& InActionTag)
{
	return UMultiplayerGameSubsystem::IsHost(this);
}

void AMatchPlayerCharacter::NetMulticast_TryExecuteAction_Implementation(const FGameplayTag& InActionTag)
{
	ActionsComponent->TryExecuteAction(InActionTag);
}

void AMatchPlayerCharacter::TryExecuteAction_Implementation(const FGameplayTag& InActionTag)
{
	IActionsInterface::TryExecuteAction_Implementation(InActionTag);
	ActionsComponent->TryExecuteAction(InActionTag);
	if (!UMultiplayerGameSubsystem::IsHost(this))
		Server_TryExecuteAction(InActionTag);
	else
		NetMulticast_TryExecuteAction(InActionTag);
}
