// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/UI/WaitWidget/Public/WaitWidget.h"

#include "Components/TextBlock.h"

void UWaitWidget::SetWaitText(const FText& InText)
{
	WaitTextBlock->SetText(InText);
}
