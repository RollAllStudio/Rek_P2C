// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/UI/HUD/Public/MainMenuHUD.h"

#include "Blueprint/UserWidget.h"
#include "TPPMulti/GameConstants/Public/GameConstants.h"
#include "TPPMulti/UI/MainMenu/Public/MainMenuWidget.h"

void AMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	MainMenuWidget = CreateWidget<UMainMenuWidget>(GetOwningPlayerController(),
		UGameConstants::GetMainMenuWidgetClass());

	MainMenuWidget->AddToViewport();
}
