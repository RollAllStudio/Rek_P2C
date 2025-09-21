// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/UI/ResourceBar/Public/ResourceBarWidget.h"

#include "ResourceInstance.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UResourceBarWidget::SetResourceInstance_Internal(UResourceInstance* InResourceInstance)
{
	UnbindResourceInstance();
	ResourceInstance = InResourceInstance;
	if (IsValid(ResourceInstance))
	{
		OnResourceChanged(ResourceTag, ResourceInstance, 0, ResourceInstance->GetCurrentValue());
		ResourceInstance->OnResourceChanged_Signature.AddUniqueDynamic(this, &UResourceBarWidget::OnResourceChanged);
	}
}

void UResourceBarWidget::UnbindResourceInstance()
{
	if (IsValid(ResourceInstance))
		ResourceInstance->OnResourceChanged_Signature.RemoveAll(this);
}

void UResourceBarWidget::OnResourceChanged(const FGameplayTag& InResourceTag, UResourceInstance* InResourceInstance,
	const float InOldValue, const float InNewValue)
{
	const float MaxValue = InResourceInstance->GetMaxValue();
	ProgressBar->SetPercent((MaxValue > 0.f) ? (InNewValue / MaxValue) : 0.f);
	const int ValueAsInt = FMath::CeilToInt(InNewValue);
	CurrentValueTextBlock->SetText(FText::FromString(FString::FromInt(ValueAsInt)));
}

void UResourceBarWidget::SetResourceInstance(UResourceInstance* InResourceInstance)
{
	if (ResourceInstance != InResourceInstance)
	{
		SetResourceInstance_Internal(InResourceInstance);
	}

	SetVisibility(IsValid(ResourceInstance) ? ESlateVisibility::SelfHitTestInvisible :
		ESlateVisibility::Collapsed);

}

void UResourceBarWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	ProgressBar->SetFillColorAndOpacity(FillColorAndOpacity);
}
