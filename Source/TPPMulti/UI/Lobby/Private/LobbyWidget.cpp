// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/UI/Lobby/Public/LobbyWidget.h"

#include "MultiplayerGameSubsystem.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "TPPMulti/GameConstants/Public/GameConstants.h"
#include "TPPMulti/UI/Lobby/Public/LobbyPlayerSlotWidget.h"

void ULobbyWidget::OnClicked_StartMatchButton()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Start match button clicked");
}

void ULobbyWidget::OnClicked_CloseSessionButton()
{
	UMultiplayerGameSubsystem::CloseSession(this);
}

void ULobbyWidget::OnServerPlayerChanged(const int32& InPlayerUID, AServerPlayerState* InServerPlayerState)
{

	ULobbyPlayerSlotWidget* SlotWidget;
	if (!PlayerSlots.Contains(InPlayerUID))
	{
		SlotWidget = CreateWidget<ULobbyPlayerSlotWidget>(GetOwningPlayer(),
			UGameConstants::GetLobbyPlayerSlotWidgetClass());

		PlayerSlots.Add(InPlayerUID, SlotWidget);

		int32 InsertIndex = 0;
		for (const auto PlayerSlot : PlayerSlots)
			if (PlayerSlot.Key < InPlayerUID)
				++InsertIndex;

		PlayerSlotsBox->InsertChildAt(InsertIndex, SlotWidget);
		
		SlotWidget->SetPlayerState(InServerPlayerState);
	}
	else
	{
		SlotWidget = PlayerSlots[InPlayerUID];
		SlotWidget->SetPlayerState(InServerPlayerState);
	}
}

void ULobbyWidget::OnServerPlayerLogout(const int32& InPlayerUID)
{
	if (PlayerSlots.Contains(InPlayerUID))
	{
		ULobbyPlayerSlotWidget* SlotWidget =
			PlayerSlots[InPlayerUID];

		if (IsValid(SlotWidget))
		{
			SlotWidget->RemoveFromParent();
			PlayerSlots.Remove(InPlayerUID);
		}
	}
}

void ULobbyWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	StartMatchButton->OnClicked.AddUniqueDynamic(this, &ULobbyWidget::OnClicked_StartMatchButton);
	CloseSessionButton->OnClicked.AddUniqueDynamic(this, &ULobbyWidget::OnClicked_CloseSessionButton);
	SessionNameBox->SetText(UMultiplayerGameSubsystem::GetLocalJoinedSessionName(this));
	StartMatchButton->SetIsEnabled(UMultiplayerGameSubsystem::IsHost(this));

	TMap<int32, AServerPlayerState*> ServerPlayers = UMultiplayerGameSubsystem::GetServerPlayers(this);
	for (auto ServerPlayer : ServerPlayers)
		OnServerPlayerChanged(ServerPlayer.Key, ServerPlayer.Value);

	UMultiplayerGameSubsystem::GetSubsystem(this)->OnServerPlayerChanged.AddUniqueDynamic(
		this, &ULobbyWidget::OnServerPlayerChanged);

	UMultiplayerGameSubsystem::GetSubsystem(this)->OnServerPlayerLogout.AddUniqueDynamic(
		this, &ULobbyWidget::OnServerPlayerLogout);

	GetOwningPlayer()->SetShowMouseCursor(true);
	
}
