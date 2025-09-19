// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/UI/HUD/Public/MatchHUD.h"

#include "Blueprint/UserWidget.h"
#include "TPPMulti/GameConstants/Public/GameConstants.h"
#include "TPPMulti/UI/HUD/Public/MatchHUDWidget.h"

void AMatchHUD::BeginPlay()
{
	Super::BeginPlay();

	MatchHUDWidget = CreateWidget<UMatchHUDWidget>(GetOwningPlayerController(),
		UGameConstants::GetMatchHUDWidgetClass());

	MatchHUDWidget->AddToViewport();
	
}
