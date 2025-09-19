// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MatchHUD.generated.h"

class UMatchHUDWidget;
/**
 * 
 */
UCLASS()
class TPPMULTI_API AMatchHUD : public AHUD
{
	GENERATED_BODY()

	UPROPERTY()
	UMatchHUDWidget* MatchHUDWidget;
	
protected:

	virtual void BeginPlay() override;
	
};
