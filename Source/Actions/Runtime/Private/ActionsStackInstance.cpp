// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/Runtime/Public/ActionsStackInstance.h"

void UActionsStackInstance::OnLockTimerTimeout()
{
	bIsLocked = false;
}

void UActionsStackInstance::Lock(const UObject* WorldContextObject, const float InLockTime)
{
	if (bIsLocked)
		Unlock(WorldContextObject);
	bIsLocked = true;

	if (InLockTime <= 0)
		return;

	WorldContextObject->GetWorld()->GetTimerManager().SetTimer(LockTimer,
		FTimerDelegate::CreateUObject(this, &UActionsStackInstance::OnLockTimerTimeout), InLockTime, false);
	
}

void UActionsStackInstance::Unlock(const UObject* WorldContextObject)
{
	WorldContextObject->GetWorld()->GetTimerManager().ClearTimer(LockTimer);
	LockTimer.Invalidate();
	bIsLocked = false;
}
