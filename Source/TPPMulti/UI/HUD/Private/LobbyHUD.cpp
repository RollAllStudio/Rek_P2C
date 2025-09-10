// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/UI/HUD/Public/LobbyHUD.h"

#include "Blueprint/UserWidget.h"
#include "TPPMulti/GameConstants/Public/GameConstants.h"
#include "TPPMulti/UI/Lobby/Public/LobbyWidget.h"

void ALobbyHUD::BeginPlay()
{
	Super::BeginPlay();

	LobbyWidget = CreateWidget<ULobbyWidget>(GetOwningPlayerController(),
		UGameConstants::GetLobbyWidgetClass());

	LobbyWidget->AddToViewport();
}
