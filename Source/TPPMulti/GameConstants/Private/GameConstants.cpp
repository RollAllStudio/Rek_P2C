// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/GameConstants/Public/GameConstants.h"

const UGameConstants* UGameConstants::Get()
{
	return GetDefault<UGameConstants>();
}

TSubclassOf<UMainMenuWidget> UGameConstants::GetMainMenuWidgetClass()
{
	return Get()->MainMenuWidgetClass;
}
