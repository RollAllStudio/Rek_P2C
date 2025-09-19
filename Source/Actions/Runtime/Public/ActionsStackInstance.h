// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ActionsStackInstance.generated.h"


UCLASS()
class ACTIONS_API UActionsStackInstance : public UObject
{
	GENERATED_BODY()

	FTimerHandle LockTimer;

	UFUNCTION()
	void OnLockTimerTimeout();

	bool bIsLocked = false;

public:

	bool IsLocked() const
	{
		return bIsLocked;
	}

	void Lock(const UObject* WorldContextObject, const float InLockTime);
	void Unlock(const UObject* WorldContextObject);
	
};
