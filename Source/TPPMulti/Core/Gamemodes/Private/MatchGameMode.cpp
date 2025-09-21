// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/Core/Gamemodes/Public/MatchGameMode.h"

#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "MultiplayerGame/Server/Public/ServerGameState.h"
#include "MultiplayerGame/Server/Public/ServerPlayerState.h"
#include "TPPMulti/Core/MatchPlayer/Public/MatchPlayerCharacter.h"
#include "TPPMulti/Core/MatchPlayer/Public/MatchPlayerController.h"
#include "TPPMulti/UI/HUD/Public/MatchHUD.h"

void AMatchGameMode::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStartActors);
}

AMatchGameMode::AMatchGameMode()
{
	PlayerControllerClass = AMatchPlayerController::StaticClass();
	DefaultPawnClass = AMatchPlayerCharacter::StaticClass();
	PlayerStateClass = AServerPlayerState::StaticClass();
	GameStateClass = AServerGameState::StaticClass();
	HUDClass = AMatchHUD::StaticClass();
}

FVector AMatchGameMode::GetRandomRespawnPosition() const
{
	const AActor* RandPlayerStart = PlayerStartActors[FMath::RandRange(0, PlayerStartActors.Num() - 1)];
	return RandPlayerStart->GetActorLocation();
}
