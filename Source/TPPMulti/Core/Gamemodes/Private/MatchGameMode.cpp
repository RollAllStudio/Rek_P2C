// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/Core/Gamemodes/Public/MatchGameMode.h"
#include "MultiplayerGameSubsystem.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "MultiplayerGame/Server/Public/ServerGameState.h"
#include "TPPMulti/Core/CoreLib/Public/CoreLibrary.h"
#include "TPPMulti/Core/MatchPlayer/Public/MatchPlayerCharacter.h"
#include "TPPMulti/Core/MatchPlayer/Public/MatchPlayerController.h"
#include "TPPMulti/Core/PlayerStates/Public/MatchPlayerState.h"
#include "TPPMulti/UI/HUD/Public/MatchHUD.h"

void AMatchGameMode::FinishMatch()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Match finished");
}

void AMatchGameMode::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStartActors);
}

AMatchGameMode::AMatchGameMode()
{
	PlayerControllerClass = AMatchPlayerController::StaticClass();
	DefaultPawnClass = AMatchPlayerCharacter::StaticClass();
	PlayerStateClass = AMatchPlayerState::StaticClass();
	GameStateClass = AServerGameState::StaticClass();
	HUDClass = AMatchHUD::StaticClass();
}

FVector AMatchGameMode::GetRandomRespawnPosition() const
{
	const AActor* RandPlayerStart = PlayerStartActors[FMath::RandRange(0, PlayerStartActors.Num() - 1)];
	return RandPlayerStart->GetActorLocation();
}

void AMatchGameMode::ScorePlayer(AMatchPlayerState* InPlayerState)
{
	InPlayerState->ScorePlayer();

	int KillsWinCondition;
	UMultiplayerGameSubsystem::FindWinConditionValue(this, WinConditionsTags::WinCondition_Kills,
		KillsWinCondition);
	
	if (InPlayerState->GetPlayerScore() >= KillsWinCondition)
	{
		FinishMatch();
		InPlayerState->IncrementWins();
	}
}
