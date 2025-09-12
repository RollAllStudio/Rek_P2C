// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/UI/MainMenu/Public/MainMenuWidget.h"

#include "MultiplayerGameConstants.h"
#include "MultiplayerGameSubsystem.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TPPMulti/Core/CoreLib/Public/CoreLibrary.h"

void UMainMenuWidget::OnClicked_HostGameButton()
{
	TMap<FName, FString> SessionSettings;
	SessionSettings.Add(
		SESSION_SETTING_NAME_SESSION_NAME,
		UMultiplayerGameSubsystem::GetLocalHostedSessionName(this).ToString());

	UMultiplayerGameSubsystem::CreateSession(SessionSettings, this);
}

void UMainMenuWidget::OnClicked_ExitGameButton()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(),
		EQuitPreference::Quit, true);
}

void UMainMenuWidget::OnCanHostChanged(const bool InNewValue)
{
	HostGameButton->SetIsEnabled(InNewValue);
}

void UMainMenuWidget::OnTextChanged_SessionNameBox(const FText& InNewText)
{
	if (!InNewText.EqualTo(SessionNameBox_CachedText) &&
		UCoreLibrary::IsTextValid(InNewText, UMultiplayerGameConstants::GetMaxSessionNameLen()))
	{
		SessionNameBox_CachedText = InNewText;
		return;
	}
	
	SessionNameBox->SetText(SessionNameBox_CachedText);

}

void UMainMenuWidget::OnTextCommitted_SessionNameBox(const FText& InNewText, ETextCommit::Type InCommitMethod)
{
	UMultiplayerGameSubsystem::SetLocalHostedSessionName(InNewText, this);
}

void UMainMenuWidget::NativeOnInitialized()
{
	
	Super::NativeOnInitialized();

	HostGameButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OnClicked_HostGameButton);
	ExitGameButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OnClicked_ExitGameButton);
	SessionNameBox->OnTextChanged.AddUniqueDynamic(this, &UMainMenuWidget::OnTextChanged_SessionNameBox);
	SessionNameBox->OnTextCommitted.AddUniqueDynamic(this, &UMainMenuWidget::OnTextCommitted_SessionNameBox);
	PlayerNameBox->OnTextChanged.AddUniqueDynamic(this, &UMainMenuWidget::OnTextChanged_PlayerNameBox);
	PlayerNameBox->OnTextCommitted.AddUniqueDynamic(this, &UMainMenuWidget::OnTextCommitted_PlayerNameBox);

	GetOwningPlayer()->SetShowMouseCursor(true);

	SessionNameBox_CachedText = UMultiplayerGameSubsystem::GetLocalHostedSessionName(this);
	SessionNameBox->SetText(SessionNameBox_CachedText);

	PlayerNameBox_CachedText = UMultiplayerGameSubsystem::GetLocalPlayerName(this);
	PlayerNameBox->SetText(PlayerNameBox_CachedText);

	OnCanHostChanged(UMultiplayerGameSubsystem::CanHostSession(this));
	UMultiplayerGameSubsystem::GetSubsystem(this)->OnCanHostSessionChanged.AddUniqueDynamic(
		this, &UMainMenuWidget::OnCanHostChanged);
	
}

void UMainMenuWidget::OnTextChanged_PlayerNameBox(const FText& InNewText)
{
	if (!InNewText.EqualTo(PlayerNameBox_CachedText) &&
		UCoreLibrary::IsTextValid(InNewText, UMultiplayerGameConstants::GetMasPlayerNameLen()))
	{
		PlayerNameBox_CachedText = InNewText;
		return;
	}

	PlayerNameBox->SetText(PlayerNameBox_CachedText);
		
}

void UMainMenuWidget::OnTextCommitted_PlayerNameBox(const FText& InNewText, ETextCommit::Type InCommitMethod)
{
	UMultiplayerGameSubsystem::SetLocalPlayerName(this, InNewText);
}
