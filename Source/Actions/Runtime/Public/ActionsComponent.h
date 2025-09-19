// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "ActionsComponent.generated.h"


class UActionsStackInstance;
class UActionsCollection;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONS_API UActionsComponent : public UActorComponent
{
	GENERATED_BODY()

#pragma region ActionsExecuting

private:

	UPROPERTY()
	TMap<FGameplayTag, UActionsStackInstance*> ActionStacks;

public:

	UFUNCTION(BlueprintPure)
	bool IsStackLocked(const FGameplayTag& InStackTag);

	UFUNCTION(BlueprintCallable)
	void LockStack(const FGameplayTag& InStackTag, const float InDuration);

	UFUNCTION(BlueprintCallable)
	void UnlockStack(const FGameplayTag& InStackTag);

	UFUNCTION(BlueprintCallable)
	void TryExecuteAction(const FGameplayTag& InActionTag);

#pragma endregion 
	
#pragma region ActionsCollection

private:

	UPROPERTY()
	UActionsCollection* ActionsCollections;

	UPROPERTY()
	FSoftObjectPath RequestedCollectionRef;
	
	UFUNCTION()
	void OnActionsCollectionLoaded(const FSoftObjectPath& InAssetPath, UObject* InAsset);
	
public:
	
	UFUNCTION(BlueprintCallable)
	void LoadActionsCollection(const TSoftObjectPtr<UActionsCollection>& InActionsCollection);

#pragma endregion 
	
};
