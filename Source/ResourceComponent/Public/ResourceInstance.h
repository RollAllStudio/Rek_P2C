// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ResourceDataTypes.h"
#include "UObject/Object.h"
#include "ResourceInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FResourceInstance_OnResourceChanged_Signature,
	const FGameplayTag&, ResourceTag,
	UResourceInstance*, ResourceInstance,
	const float, OldValue,
	const float, NewValue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FResourceInstance_OnResourceDepleted_Signature,
	const FGameplayTag&, ResourceTag,
	UResourceInstance*, ResourceInstance);

UCLASS()
class RESOURCECOMPONENT_API UResourceInstance : public UObject , public FTickableGameObject
{
	GENERATED_BODY()

#pragma region TickableAPI
	
public:
	
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;
	virtual bool IsTickable() const override;
	bool bShouldTick = true;

#pragma endregion

private:

	FGameplayTag ResourceTag;
	float CurrentValue;
	float MaxValue;
	float RegenSpeed;
	bool bIsDepleted;
	bool bCanRegenWhenDepleted;
	
	bool CanRegen() const;
	void SetResourceValue_Internal(const float InValue);
	
public:

	UPROPERTY(BlueprintAssignable)
	FResourceInstance_OnResourceChanged_Signature OnResourceChanged_Signature;

	UPROPERTY(BlueprintAssignable)
	FResourceInstance_OnResourceDepleted_Signature OnResourceDepleted;

	void Setup(const FGameplayTag& InResourceTag, const FResourceInitData& InInitData);
	void ConsumeResource(const float InValue);
	void AddResource(const float InValue);
	
	float GetCurrentValue() const
	{
		return CurrentValue;
	}

	float GetMaxValue() const
	{
		return MaxValue;
	}

	bool GetIsDepleted() const
	{
		return bIsDepleted;
	}

	float GetRegenSpeed() const
	{
		return RegenSpeed;
	}

	bool GetCanRegenWhenDepleted() const
	{
		return bCanRegenWhenDepleted;
	}

	void SetResourceValue(const float InValue);
	void UpdateWithRepData(const FReplicatedResourceData& InRepData);
	
};
