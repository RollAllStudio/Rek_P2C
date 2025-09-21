// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/UI/Lobby/Public/LobbyWidget.h"
#include "MultiplayerGameConstants.h"
#include "MultiplayerGameSubsystem.h"
#include "NativeGameplayTags.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"
#include "TPPMulti/Core/CoreLib/Public/CoreLibrary.h"
#include "TPPMulti/Core/GameStates/Public/LobbyGameState.h"
#include "TPPMulti/Core/PlayerStates/Public/LobbyPlayerState.h"
#include "TPPMulti/GameConstants/Public/GameConstants.h"
#include "TPPMulti/UI/Lobby/Public/LobbyPlayerSlotWidget.h"

void ULobbyWidget::OnClicked_StartMatchButton()
{
	ALobbyGameState* LobbyGameState = Cast<ALobbyGameState>(UGameplayStatics::GetGameState(this));
	LobbyGameState->NetMulticast_StartTravelToMatchWorld();
	UMultiplayerGameSubsystem::TravelToMap(this, UGameConstants::GetMatchWorldPath());
}

void ULobbyWidget::OnClicked_ReadyButton()
{
	ALobbyPlayerState* LobbyPlayerState = GetOwningPlayer()->GetPlayerState<ALobbyPlayerState>();
	if (IsValid(LobbyPlayerState))
		LobbyPlayerState->SetIsReady(!LobbyPlayerState->GetIsReady());
}

void ULobbyWidget::OnClicked_CloseSessionButton()
{
	UMultiplayerGameSubsystem::CloseSession(this);
}

void ULobbyWidget::OnTextCommitted_WinConditionTextBox(const FText& Text, ETextCommit::Type CommitMethod)
{
	const FString AsString = Text.ToString();
	if (AsString.IsNumeric())
	{
		const int AsInt = FCString::Atoi(*AsString);
		if (AsInt > 0)
		{
			CachedWinConditionText = Text;
			UMultiplayerGameSubsystem::SetWinCondition(this,
				WinConditionsTags::WinCondition_Kills, AsInt);

			ALobbyGameState* LobbyGameState = Cast<ALobbyGameState>(
				UGameplayStatics::GetGameState(this));
			LobbyGameState->SetWinConditionKills(AsInt);
			
			return;
		}
	}

	WinConditionTextBox->SetText(CachedWinConditionText);
	
}

void ULobbyWidget::OnServerPlayerChanged(const int32& InPlayerUID, AServerPlayerState* InServerPlayerState)
{

	ALobbyPlayerState* LobbyPlayerState = Cast<ALobbyPlayerState>(InServerPlayerState);
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
		SlotWidget->SetPlayerState(LobbyPlayerState);
	}
	else
	{
		SlotWidget = PlayerSlots[InPlayerUID];
		SlotWidget->SetPlayerState(LobbyPlayerState);
	}

	OnPlayerReadyChanged(true);
	if (IsValid(LobbyPlayerState))
		LobbyPlayerState->OnIsReadyChanged.AddUniqueDynamic(this, &ULobbyWidget::OnPlayerReadyChanged);
	
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

void ULobbyWidget::OnPlayerReadyChanged(const bool InNewIsReady)
{

	TMap<int32, AServerPlayerState*> ServerPlayers = UMultiplayerGameSubsystem::GetServerPlayers(this);
	for (const auto ServerPlayer : ServerPlayers)
	{
		ALobbyPlayerState* AsLobbyPlayerState = Cast<ALobbyPlayerState>(ServerPlayer.Value);
		if (IsValid(AsLobbyPlayerState))
		{
			if (!AsLobbyPlayerState->GetIsReady())
			{
				StartMatchButton->SetIsEnabled(false);
				return;
			}
		}
	}

	StartMatchButton->SetIsEnabled(true);
	
}

void ULobbyWidget::OnWinConditionKillsChanged(const int InValue)
{
	WinConditionTextBox->SetText(FText::FromString(FString::FromInt(InValue)));
}

void ULobbyWidget::UpdateWinConditionText(const int InValue)
{
	CachedWinConditionText = FText::FromString(FString::FromInt(InValue));
	WinConditionTextBox->SetText(CachedWinConditionText);
	ALobbyGameState* LobbyGameState = Cast<ALobbyGameState>(
				UGameplayStatics::GetGameState(this));
	LobbyGameState->SetWinConditionKills(InValue);
	UMultiplayerGameSubsystem::SetWinCondition(this, WinConditionsTags::WinCondition_Kills, InValue);
}

void ULobbyWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CloseSessionButton->OnClicked.AddUniqueDynamic(this, &ULobbyWidget::OnClicked_CloseSessionButton);
	SessionNameBox->SetText(UMultiplayerGameSubsystem::GetLocalJoinedSessionName(this));
	StartMatchButton->SetIsEnabled(UMultiplayerGameSubsystem::IsHost(this));

	if (UMultiplayerGameSubsystem::IsHost(this))
	{
		OnPlayerReadyChanged(true);
		StartMatchButton->SetVisibility(ESlateVisibility::Visible);
		StartMatchButton->OnClicked.AddUniqueDynamic(this, &ULobbyWidget::OnClicked_StartMatchButton);
	}
	else
	{
		StartMatchButton->SetVisibility(ESlateVisibility::Collapsed);
		StartMatchButton->SetIsEnabled(false);
	}

	ReadyButton->SetVisibility(ESlateVisibility::Visible);
	ReadyButton->OnClicked.AddUniqueDynamic(this, &ULobbyWidget::OnClicked_ReadyButton);
	
	TMap<int32, AServerPlayerState*> ServerPlayers = UMultiplayerGameSubsystem::GetServerPlayers(this);
	for (auto ServerPlayer : ServerPlayers)
	{
		OnServerPlayerChanged(ServerPlayer.Key, ServerPlayer.Value);
		ALobbyPlayerState* AsLobbyPlayerState = Cast<ALobbyPlayerState>(ServerPlayer.Value);
		if (IsValid(AsLobbyPlayerState))
			AsLobbyPlayerState->OnIsReadyChanged.AddUniqueDynamic(this, &ULobbyWidget::OnPlayerReadyChanged);
	}

	UMultiplayerGameSubsystem::GetSubsystem(this)->OnServerPlayerChanged.AddUniqueDynamic(
		this, &ULobbyWidget::OnServerPlayerChanged);

	UMultiplayerGameSubsystem::GetSubsystem(this)->OnServerPlayerLogout.AddUniqueDynamic(
		this, &ULobbyWidget::OnServerPlayerLogout);
	
	GetOwningPlayer()->SetShowMouseCursor(true);

	ALobbyGameState* LobbyGameState = Cast<ALobbyGameState>(UGameplayStatics::GetGameState(this));
	LobbyGameState->OnStartTravelToMatchWorld.AddUniqueDynamic(this, &ULobbyWidget::OnStartTravelToMatchWorld);

	if (UMultiplayerGameSubsystem::IsHost(this))
	{
		int WinConditionValue;
		if (UMultiplayerGameSubsystem::FindWinConditionValue(this,
			WinConditionsTags::WinCondition_Kills, WinConditionValue))
		{
			UpdateWinConditionText(WinConditionValue);
		}
		else
		{
			UMultiplayerGameConstants::FindDefaultWinCondition(WinConditionsTags::WinCondition_Kills, WinConditionValue);
			UpdateWinConditionText(WinConditionValue);
		}

		WinConditionTextBox->OnTextCommitted.AddUniqueDynamic(this, &ULobbyWidget::OnTextCommitted_WinConditionTextBox);
		WinConditionTextBox->SetIsEnabled(true);
	}
	else
	{
		WinConditionTextBox->SetIsEnabled(false);
		OnWinConditionKillsChanged(LobbyGameState->GetWinConditionKills());
		LobbyGameState->OnWinConditionKillsChanged.AddUniqueDynamic(this, &ULobbyWidget::OnWinConditionKillsChanged);
	}
	
}
