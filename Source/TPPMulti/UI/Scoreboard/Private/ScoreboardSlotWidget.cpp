// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/UI/Scoreboard/Public/ScoreboardSlotWidget.h"

#include "Components/TextBlock.h"
#include "TPPMulti/Core/PlayerStates/Public/MatchPlayerState.h"

void UScoreboardSlotWidget::OnPlayerScoreChanged(const int InNewScore)
{
	PlayerScoreTextBlock->SetText(FText::FromString(FString::FromInt(InNewScore)));
}

void UScoreboardSlotWidget::OnPlayerNameChanged(const FString& InNewName)
{
	PlayerNameTextBlock->SetText(FText::FromString(InNewName));
}

void UScoreboardSlotWidget::SetPlayerState(AMatchPlayerState* InPlayerState)
{
	PlayerState = InPlayerState;
	OnPlayerScoreChanged(PlayerState->GetPlayerScore());
	OnPlayerNameChanged(PlayerState->GetServerPlayerName());

	PlayerState->OnServerNameChanged.AddUniqueDynamic(this, &UScoreboardSlotWidget::OnPlayerNameChanged);
	PlayerState->OnPlayerScoreChanged.AddUniqueDynamic(this, &UScoreboardSlotWidget::OnPlayerScoreChanged);
	
}
