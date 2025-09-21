// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/UI/HUD/Public/MatchHUDWidget.h"
#include "MultiplayerGameSubsystem.h"
#include "ResourceInstance.h"
#include "ResourcesComponent.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "MultiplayerGame/Server/Public/ServerPlayerState.h"
#include "TPPMulti/Core/MatchPlayer/Public/MatchPlayerController.h"
#include "TPPMulti/UI/ResourceBar/Public/ResourceBarWidget.h"

void UMatchHUDWidget::OnPlayerWin(const int32& InPlayerUID)
{
	AServerPlayerState* WinnerPlayerState =
		UMultiplayerGameSubsystem::GetServerPlayerState(this, InPlayerUID);
	WinnerNameBox->SetText(FText::FromString(WinnerPlayerState->GetServerPlayerName()));
	MainSwitcher->SetActiveWidgetIndex(1);
}

void UMatchHUDWidget::OnControllerPawnChanged(APawn* InNewPawn)
{
	
	ClearResourcesBars();

	if (!IsValid(InNewPawn))
		return;
	
	if (IsValid(ResourcesComponent))
		ResourcesComponent->OnAnyResourceInitialized.RemoveAll(this);
	ResourcesComponent = InNewPawn->GetComponentByClass<UResourcesComponent>();

	if (IsValid(ResourcesComponent))
	{
		UResourceInstance* BufferResourceInstance;
		ResourcesComponent->OnAnyResourceInitialized.AddUniqueDynamic(this,
			&UMatchHUDWidget::OnResourceInitialized);

#define INIT_SETUP_RESOURCE_BAR(Widget) \
		if (ResourcesComponent->FindResourceInstance( Widget ->GetResourceTag(), BufferResourceInstance)) \
			Widget ->SetResourceInstance(BufferResourceInstance);

		INIT_SETUP_RESOURCE_BAR(HealthBar)
		INIT_SETUP_RESOURCE_BAR(StaminaBar)
		INIT_SETUP_RESOURCE_BAR(ManaBar)

#undef INIT_SETUP_RESOURCE_BAR
		
	}
}

void UMatchHUDWidget::OnResourceInitialized(const FGameplayTag& InResourceTag)
{
	UResourceInstance* ResourceInstance;

#define CALLBACK_SETUP_RESOURCE_BAR(Widget) \
	if ( Widget ->GetResourceTag() == InResourceTag) \
	{ ResourcesComponent->FindResourceInstance(InResourceTag, ResourceInstance); \
	Widget ->SetResourceInstance(ResourceInstance); }

	CALLBACK_SETUP_RESOURCE_BAR(HealthBar)
	CALLBACK_SETUP_RESOURCE_BAR(StaminaBar)
	CALLBACK_SETUP_RESOURCE_BAR(ManaBar)

#undef CALLBACK_SETUP_RESOURCE_BAR
	
}

void UMatchHUDWidget::ClearResourcesBars()
{
	HealthBar->SetResourceInstance(nullptr);
	StaminaBar->SetResourceInstance(nullptr);
	ManaBar->SetResourceInstance(nullptr);
}

void UMatchHUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	MainSwitcher->SetActiveWidgetIndex(0);
	AMatchPlayerController* MatchPlayerController =
		Cast<AMatchPlayerController>(GetOwningPlayer());

	OnControllerPawnChanged(MatchPlayerController->GetPawn());
	MatchPlayerController->OnNewPawnSet_Signature.AddUniqueDynamic(this, &UMatchHUDWidget::OnControllerPawnChanged);
	MatchPlayerController->OnPlayerWin.AddUniqueDynamic(this, &UMatchHUDWidget::OnPlayerWin);
}
