// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/Core/MatchPlayer/Public/MatchPlayerCharacter.h"

#include "MultiplayerGameSubsystem.h"
#include "NativeGameplayTags.h"
#include "Actions/Runtime/Public/ActionsComponent.h"
#include "Camera/CameraComponent.h"
#include "DynamicMeshSpawner/Runtime/Public/DynamicMeshSpawnerComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
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

float AMatchPlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Damage Taken");
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
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

FTransform AMatchPlayerCharacter::GetSpellInitialTransform_Implementation()
{
	const FVector SpawnLocation = GetMesh()->GetSocketLocation(CharacterData.SpellSpawnSocket);
	const FVector SpawnScale = FVector(1);

	const FVector CameraForwardVector = CameraComponent->GetForwardVector();
	const FVector TraceEndLocation = CameraComponent->GetComponentLocation() + CameraForwardVector *
		UGameConstants::GetSpellTargetTraceLen();

	FHitResult CameraHitResult;
	UKismetSystemLibrary::LineTraceSingle(this, SpawnLocation, TraceEndLocation,
		TraceTypeQuery2, true, {this}, EDrawDebugTrace::None,
		CameraHitResult, true);

	FVector TargetLocation;
	if (CameraHitResult.IsValidBlockingHit())
		TargetLocation = CameraHitResult.Location;
	else
		TargetLocation = TraceEndLocation;

	const FRotator SpawnRotation = UKismetMathLibrary::FindLookAtRotation(SpawnLocation, TargetLocation);
	
	return FTransform(SpawnRotation, SpawnLocation, SpawnScale);
}

APawn* AMatchPlayerCharacter::GetSpellInstigatorPawn_Implementation()
{
	return this;
}
