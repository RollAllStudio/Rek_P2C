// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/UI/Scoreboard/Public/ScoreboardWidget.h"

#include "MultiplayerGameSubsystem.h"
#include "Components/VerticalBox.h"
#include "TPPMulti/Core/PlayerStates/Public/MatchPlayerState.h"
#include "TPPMulti/GameConstants/Public/GameConstants.h"
#include "TPPMulti/UI/Scoreboard/Public/ScoreboardSlotWidget.h"

void UScoreboardWidget::OnServerPlayerChanged(const int32& UID, AServerPlayerState* PlayerState)
{
	RefreshPlayersList();
}

void UScoreboardWidget::RefreshPlayersList()
{

	SlotsBox->ClearChildren();
	TMap<int32, AServerPlayerState*> PlayersList =
		UMultiplayerGameSubsystem::GetServerPlayers(this);

	for (auto ServerPlayer : PlayersList)
	{
		AMatchPlayerState* MatchPlayerState = Cast<AMatchPlayerState>(ServerPlayer.Value);
		if (IsValid(MatchPlayerState))
			CreatePlayerSlot(MatchPlayerState);
	}
	
}

void UScoreboardWidget::CreatePlayerSlot(AMatchPlayerState* InPlayerState)
{
	UScoreboardSlotWidget* NewSlot = CreateWidget<UScoreboardSlotWidget>(GetOwningPlayer(),
		UGameConstants::GetScoreboardSlotWidgetClass());
	NewSlot->SetPlayerState(InPlayerState);
	SlotsBox->AddChild(NewSlot);
}

void UScoreboardWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	RefreshPlayersList();
	UMultiplayerGameSubsystem::GetSubsystem(this)->OnServerPlayerChanged.AddUniqueDynamic(
		this, &UScoreboardWidget::OnServerPlayerChanged);
}
