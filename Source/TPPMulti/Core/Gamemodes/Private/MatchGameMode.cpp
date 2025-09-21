// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/Core/Gamemodes/Public/MatchGameMode.h"

#include "MultiplayerGameConstants.h"
#include "MultiplayerGameSubsystem.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "MultiplayerGame/Server/Public/ServerGameState.h"
#include "TPPMulti/Core/CoreLib/Public/CoreLibrary.h"
#include "TPPMulti/Core/MatchPlayer/Public/MatchPlayerCharacter.h"
#include "TPPMulti/Core/MatchPlayer/Public/MatchPlayerController.h"
#include "TPPMulti/Core/PlayerStates/Public/MatchPlayerState.h"
#include "TPPMulti/GameConstants/Public/GameConstants.h"
#include "TPPMulti/UI/HUD/Public/MatchHUD.h"

void AMatchGameMode::FinishMatch(const int32& InWinnerUID)
{
	for (auto LoggedPlayer : LoggedPlayers)
	{
		AMatchPlayerController* MatchLoggedPlayer =
			Cast<AMatchPlayerController>(LoggedPlayer);

		if (IsValid(MatchLoggedPlayer))
			MatchLoggedPlayer->NetMulticast_OnPlayerWin(InWinnerUID);
	}

	GetWorld()->GetTimerManager().SetTimer(PostFinishMatchTimer, FTimerDelegate::CreateUObject(
		this, &AMatchGameMode::TravelToLobby), UGameConstants::GetFinishMatchWidgetDisplayTime(), false);
	
}

void AMatchGameMode::TravelToLobby()
{
	UMultiplayerGameSubsystem::TravelToMap(this, UMultiplayerGameConstants::GetLobbyWorldPath());
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
		FinishMatch(InPlayerState->GetServerUID());
		InPlayerState->IncrementWins();
	}
}
