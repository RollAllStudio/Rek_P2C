// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/UI/HUD/Public/MatchHUDWidget.h"

#include "MultiplayerGameSubsystem.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "MultiplayerGame/Server/Public/ServerPlayerState.h"
#include "TPPMulti/Core/MatchPlayer/Public/MatchPlayerController.h"

void UMatchHUDWidget::OnPlayerWin(const int32& InPlayerUID)
{

	AServerPlayerState* WinnerPlayerState =
		UMultiplayerGameSubsystem::GetServerPlayerState(this, InPlayerUID);
	WinnerNameBox->SetText(FText::FromString(WinnerPlayerState->GetServerPlayerName()));
	MainSwitcher->SetActiveWidgetIndex(1);
}

void UMatchHUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	MainSwitcher->SetActiveWidgetIndex(0);
	AMatchPlayerController* MatchPlayerController =
		Cast<AMatchPlayerController>(GetOwningPlayer());

	MatchPlayerController->OnPlayerWin.AddUniqueDynamic(this, &UMatchHUDWidget::OnPlayerWin);
}
