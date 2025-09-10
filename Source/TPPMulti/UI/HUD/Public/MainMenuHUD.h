// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuHUD.generated.h"

class UMainMenuWidget;
/**
 * 
 */
UCLASS()
class TPPMULTI_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()

private:

	UPROPERTY(BlueprintGetter = GetMainMenuWidget)
	UMainMenuWidget* MainMenuWidget;

public:

	UFUNCTION(BlueprintGetter)
	UMainMenuWidget* GetMainMenuWidget() const
	{
		return MainMenuWidget;
	}
	
protected:

	void BeginPlay() override;
	
};
