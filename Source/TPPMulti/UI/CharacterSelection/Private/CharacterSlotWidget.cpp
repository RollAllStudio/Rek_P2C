// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/UI/CharacterSelection/Public/CharacterSlotWidget.h"

#include "MultiplayerGameSubsystem.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "TPPMulti/CharactersDataBase/Public/CharactersDataBase.h"
#include "TPPMulti/Core/PlayerStates/Public/LobbyPlayerState.h"

void UCharacterSlotWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	SelectButton->SetVisibility(ESlateVisibility::Visible);
	CharacterImage->SetVisibility(ESlateVisibility::HitTestInvisible);
	CharacterNameTextBlock->SetVisibility(ESlateVisibility::HitTestInvisible);
	SelectButton->OnClicked.AddUniqueDynamic(this, &UCharacterSlotWidget::Select);
}

void UCharacterSlotWidget::Select()
{
	OnPreSelect.Broadcast();
	SetIsSelected(true);
	ALobbyPlayerState* LobbyPlayerState = Cast<ALobbyPlayerState>(UMultiplayerGameSubsystem::GetServerPlayerState(
		this, UMultiplayerGameSubsystem::GetLocalPlayerUID(this)));

	if (IsValid(LobbyPlayerState))
		LobbyPlayerState->SetCharacterRow(CharacterRow);
}

void UCharacterSlotWidget::SetCharacterRow(const FDataTableRowHandle& InCharacterRow)
{
	if (CharacterRow != InCharacterRow)
	{
		CharacterRow = InCharacterRow;
		FCharacterData CharacterData;
		UCharactersDataBase::ReadCharacterData(CharacterRow, CharacterData);
		CharacterImage->SetBrush(CharacterData.DisplayImage);
		CharacterNameTextBlock->SetText(CharacterData.DisplayName);
	}
}

void UCharacterSlotWidget::SetIsSelected(const bool InIsSelected)
{
	bIsSelected = InIsSelected;
	SelectButton->SetIsEnabled(!bIsSelected);
}
