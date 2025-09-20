// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceInstance.h"


void UResourceInstance::Tick(float DeltaTime)
{
	if (CanRegen())
		AddResource(DeltaTime * RegenSpeed);
}

TStatId UResourceInstance::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UResourceInstance, STATGROUP_Tickables);
}

bool UResourceInstance::IsTickable() const
{
	return bShouldTick && !IsTemplate();
}

bool UResourceInstance::CanRegen() const
{
	return (bCanRegenWhenDepleted || !bIsDepleted) && RegenSpeed > 0;
}

void UResourceInstance::SetResourceValue_Internal(const float InValue)
{
	const float OldValue = CurrentValue;
	const float NewValue = FMath::Clamp(InValue, 0, MaxValue);
	if (OldValue != NewValue)
	{
		CurrentValue = NewValue;
		if (CurrentValue <= KINDA_SMALL_NUMBER)
		{
			if (!bIsDepleted)
			{
				bIsDepleted = true;
				OnResourceDepleted.Broadcast(ResourceTag, this);
			}
		}
		else
		{
			bIsDepleted = false;
		}

		OnResourceChanged_Signature.Broadcast(ResourceTag, this, OldValue, CurrentValue);
		
	}
}

void UResourceInstance::Setup(const FGameplayTag& InResourceTag, const FResourceInitData& InInitData)
{
	ResourceTag = InResourceTag;
	MaxValue = InInitData.InitValue;
	SetResourceValue_Internal(MaxValue);
	RegenSpeed = InInitData.RegenSpeed;
	bCanRegenWhenDepleted = InInitData.bCanRegenWhenDepleted;
}

void UResourceInstance::ConsumeResource(const float InValue)
{
	SetResourceValue_Internal(CurrentValue - InValue);
}

void UResourceInstance::AddResource(const float InValue)
{
	SetResourceValue_Internal(CurrentValue + InValue);
}

void UResourceInstance::SetResourceValue(const float InValue)
{
	SetResourceValue_Internal(InValue);
}

void UResourceInstance::UpdateWithRepData(const FReplicatedResourceData& InRepData)
{
	MaxValue = InRepData.MaxValue;
	SetResourceValue_Internal(InRepData.CurrentValue);
	RegenSpeed = InRepData.RegenSpeed;
	bCanRegenWhenDepleted = InRepData.bCanRegenWhenDepleted;
}

