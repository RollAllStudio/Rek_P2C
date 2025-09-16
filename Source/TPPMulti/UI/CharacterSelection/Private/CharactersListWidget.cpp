// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/UI/CharacterSelection/Public/CharactersListWidget.h"
#include "MultiplayerGameSubsystem.h"
#include "Components/HorizontalBox.h"
#include "MultiplayerGame/Server/Public/ServerPlayerState.h"
#include "TPPMulti/GameConstants/Public/GameConstants.h"
#include "TPPMulti/UI/CharacterSelection/Public/CharacterSlotWidget.h"

void UCharactersListWidget::OnServerPlayerChanged(const int32& InPlayerUID, AServerPlayerState* InPlayerState)
{
	const int32 LocalPlayerUID = UMultiplayerGameSubsystem::GetLocalPlayerUID(this);
	if (LocalPlayerUID != INDEX_NONE && LocalPlayerUID == InPlayerUID)
	{
		FDataTableRowHandle CurrentRowHandle;
		CurrentRowHandle.DataTable = CharactersDataTable;
		TArray<FName> Rows = CharactersDataTable->GetRowNames();
		for (const auto RowName : Rows)
		{
			CurrentRowHandle.RowName = RowName;
			UCharacterSlotWidget* NewSlot = CreateWidget<UCharacterSlotWidget>(GetOwningPlayer(),
				UGameConstants::GetCharacterSlotWidgetClass());
			NewSlot->SetCharacterRow(CurrentRowHandle);
			NewSlot->OnPreSelect.AddUniqueDynamic(this, &UCharactersListWidget::OnPreSelectSlot);
			Slots.Add(NewSlot);
			SlotsBox.Get()->AddChild(NewSlot);
		}

		if (Slots.Num() > 0)
			Slots[0]->Select();
	}
}

void UCharactersListWidget::OnPreSelectSlot()
{
	for (auto LocalSlot : Slots)
		LocalSlot->SetIsSelected(false);
}

void UCharactersListWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	const int32 LocalPlayerUID = UMultiplayerGameSubsystem::GetLocalPlayerUID(this);
	if (LocalPlayerUID != INDEX_NONE)
	{
		TMap<int32, AServerPlayerState*> ServerPlayers = UMultiplayerGameSubsystem::GetServerPlayers(this);
		if (ServerPlayers.Contains(LocalPlayerUID))
			if (IsValid(ServerPlayers[LocalPlayerUID]))
				OnServerPlayerChanged(LocalPlayerUID, ServerPlayers[LocalPlayerUID]);
	}

	UMultiplayerGameSubsystem::GetSubsystem(this)->OnServerPlayerChanged.AddUniqueDynamic(
		this, &UCharactersListWidget::OnServerPlayerChanged);
	
}
