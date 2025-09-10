// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/UI/MainMenu/Public/MainMenuWidget.h"

#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/KismetSystemLibrary.h"

void UMainMenuWidget::OnClicked_HostGameButton()
{
}

void UMainMenuWidget::OnClicked_ExitGameButton()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(),
		EQuitPreference::Quit, true);
}

void UMainMenuWidget::OnTextChanged_SessionNameBox(const FText& InNewText)
{
}

void UMainMenuWidget::OnTextCommitted_SessionNameBox(const FText& InNewText, ETextCommit::Type InCommitMethod)
{
}

void UMainMenuWidget::NativeOnInitialized()
{
	
	Super::NativeOnInitialized();

	HostGameButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OnClicked_HostGameButton);
	ExitGameButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OnClicked_ExitGameButton);
	SessionNameBox->OnTextChanged.AddUniqueDynamic(this, &UMainMenuWidget::OnTextChanged_SessionNameBox);
	SessionNameBox->OnTextCommitted.AddUniqueDynamic(this, &UMainMenuWidget::OnTextCommitted_SessionNameBox);

	GetOwningPlayer()->SetShowMouseCursor(true);
	
}
