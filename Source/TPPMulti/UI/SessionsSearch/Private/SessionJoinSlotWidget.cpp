// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/UI/SessionsSearch/Public/SessionJoinSlotWidget.h"

#include "MultiplayerGameSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void USessionJoinSlotWidget::OnClicked_JoinSessionButton()
{
	UMultiplayerGameSubsystem::JoinSessionByIndex(this, SessionIndex);
}

void USessionJoinSlotWidget::SetupSlot(const int32& InSearchIndex,
	const FOnlineSessionSearchResult& InSessionSearchResult)
{
	SessionIndex = InSearchIndex;

	const float Ping = InSessionSearchResult.PingInMs;
	const int MaxPlayers = InSessionSearchResult.Session.SessionSettings.NumPublicConnections;
	const int OpenConnections = InSessionSearchResult.Session.NumOpenPublicConnections;
	const int CurrentPlayers = MaxPlayers - OpenConnections;
	FString SessionName;
	InSessionSearchResult.Session.SessionSettings.Get(SESSION_SETTING_NAME_SESSION_NAME, SessionName);

	SessionNameTextBlock->SetText(FText::FromString(SessionName));

	FString PlayersAmountTextBuilder = FString::FromInt(CurrentPlayers);
	PlayersAmountTextBuilder.Append(" / ");
	PlayersAmountTextBuilder.Append(FString::FromInt(MaxPlayers));
	PlayersAmountTextBlock->SetText(FText::FromString(PlayersAmountTextBuilder));

	PingTextBlock->SetText(FText::FromString(FString::SanitizeFloat(Ping)));
	
}

void USessionJoinSlotWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	JoinSessionButton.Get()->OnClicked.AddUniqueDynamic(this, &USessionJoinSlotWidget::OnClicked_JoinSessionButton);
}
