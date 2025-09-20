// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ResourceDataTypes.generated.h"

USTRUCT(BlueprintType)
struct FResourceInitData
{
	
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InitValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RegenSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanRegenWhenDepleted;	
};

USTRUCT(BlueprintType)
struct FReplicatedResourceData
{
	
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag ResourceTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RegenSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanRegenWhenDepleted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDepleted;

	FReplicatedResourceData(): CurrentValue(0), MaxValue(0), RegenSpeed(0), bCanRegenWhenDepleted(false),
	                           bDepleted(false)
	{
	}
};