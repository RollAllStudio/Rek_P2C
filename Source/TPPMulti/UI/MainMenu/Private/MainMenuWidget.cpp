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
		UMultiplayerGameSubsystem::GetLocalSessionName(this).ToString());

	UMultiplayerGameSubsystem::CreateSession(SessionSettings, this);
}

void UMainMenuWidget::OnClicked_ExitGameButton()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(),
		EQuitPreference::Quit, true);
}

void UMainMenuWidget::OnTextChanged_SessionNameBox(const FText& InNewText)
{
	if (!InNewText.EqualTo(SessionNameBox_CachedText) &&
		UCoreLibrary::IsTextValid(InNewText, UMultiplayerGameConstants::GetMaxSessionNameLen()))
		SessionNameBox_CachedText = InNewText;
}

void UMainMenuWidget::OnTextCommitted_SessionNameBox(const FText& InNewText, ETextCommit::Type InCommitMethod)
{
	UMultiplayerGameSubsystem::SetLocalSessionName(InNewText, this);
}

void UMainMenuWidget::OnLocalSessionNameChanged(const FText& InNewSessionName)
{
	HostGameButton->SetIsEnabled(!InNewSessionName.IsEmpty());
}

void UMainMenuWidget::NativeOnInitialized()
{
	
	Super::NativeOnInitialized();

	HostGameButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OnClicked_HostGameButton);
	ExitGameButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OnClicked_ExitGameButton);
	SessionNameBox->OnTextChanged.AddUniqueDynamic(this, &UMainMenuWidget::OnTextChanged_SessionNameBox);
	SessionNameBox->OnTextCommitted.AddUniqueDynamic(this, &UMainMenuWidget::OnTextCommitted_SessionNameBox);

	GetOwningPlayer()->SetShowMouseCursor(true);

	SessionNameBox_CachedText = UMultiplayerGameSubsystem::GetLocalSessionName(this);
	SessionNameBox->SetText(SessionNameBox_CachedText);
	OnLocalSessionNameChanged(SessionNameBox_CachedText);
	UMultiplayerGameSubsystem* MultiplayerGameSubsystem =
		UMultiplayerGameSubsystem::GetSubsystem(this);

	MultiplayerGameSubsystem->OnLocalSessionNameChanged.AddUniqueDynamic(
		this, &UMainMenuWidget::OnLocalSessionNameChanged);

	
}
