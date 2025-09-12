// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/UI/Lobby/Public/LobbyWidget.h"

#include "MultiplayerGameSubsystem.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void ULobbyWidget::OnClicked_StartMatchButton()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Start match button clicked");
}

void ULobbyWidget::OnClicked_CloseSessionButton()
{
	UMultiplayerGameSubsystem::CloseSession(this);
}

void ULobbyWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	StartMatchButton->OnClicked.AddUniqueDynamic(this, &ULobbyWidget::OnClicked_StartMatchButton);
	CloseSessionButton->OnClicked.AddUniqueDynamic(this, &ULobbyWidget::OnClicked_CloseSessionButton);
	SessionNameBox->SetText(UMultiplayerGameSubsystem::GetLocalJoinedSessionName(this));
	StartMatchButton->SetIsEnabled(UMultiplayerGameSubsystem::IsHost(this));

	GetOwningPlayer()->SetShowMouseCursor(true);
	
}
