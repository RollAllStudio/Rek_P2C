// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/UI/SessionsSearch/Public/SessionsBrowserWidget.h"

#include "MultiplayerGameSubsystem.h"
#include "SessionsFindResult.h"
#include "Components/VerticalBox.h"
#include "TPPMulti/GameConstants/Public/GameConstants.h"
#include "TPPMulti/UI/SessionsSearch/Public/SessionJoinSlotWidget.h"

void USessionsBrowserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	UMultiplayerGameSubsystem::GetSubsystem(this)->OnSessionsFindComplete.AddUniqueDynamic(
		this, &USessionsBrowserWidget::OnSessionsSearchComplete);
	UMultiplayerGameSubsystem::StartFindSessionsLoop(this);
}

void USessionsBrowserWidget::NativeDestruct()
{
	Super::NativeDestruct();
	UMultiplayerGameSubsystem::StopFindSessionsLoop(this);
}

void USessionsBrowserWidget::OnSessionsSearchComplete(USessionsFindResult* InFindResult)
{
	TSharedPtr<FOnlineSessionSearch> SessionSearchPtr = InFindResult->GetSearchPtr();
	TArray<FOnlineSessionSearchResult> FoundSessions = SessionSearchPtr.Get()->SearchResults;
	SessionsBox.Get()->ClearChildren();
	for (int32 i = 0; i < FoundSessions.Num(); i++)
	{
		USessionJoinSlotWidget* NewSessionSlot =
			CreateWidget<USessionJoinSlotWidget>(GetOwningPlayer(), UGameConstants::GetSessionJoinWidgetSlotClass());

		NewSessionSlot->SetupSlot(i, FoundSessions[i]);
		SessionsBox.Get()->AddChild(NewSessionSlot);
	}
}
