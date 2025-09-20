// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ResourceDataTypes.h"
#include "Components/ActorComponent.h"
#include "ResourcesComponent.generated.h"

class UResourceInstance;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FResourcesComponent_OnAnyResourceChanged_Signature,
	const FGameplayTag&, ResourceTag);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RESOURCECOMPONENT_API UResourcesComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
private:
	
	UPROPERTY()
	TMap<FGameplayTag, UResourceInstance*> ResourceInstances;

	UPROPERTY(ReplicatedUsing = OnRep_ResourcesData)
	TArray<FReplicatedResourceData> ResourcesRepData;

	void UpdateReplicatedResource(const FGameplayTag& InResourceTag, UResourceInstance* InResourceInstance);
	void UpdateLocalResource(const FGameplayTag& InResourceTag, const FReplicatedResourceData& InResourceData);
	
	UFUNCTION()
	void OnRep_ResourcesData();

	UFUNCTION()
	void OnResourceChanged(const FGameplayTag& InResourceTag, UResourceInstance* InResourceInstance,
		const float InOldValue, const float InNewValue);

	UFUNCTION()
	void OnResourceDepleted(const FGameplayTag& InResourceTag, UResourceInstance* InResourceInstance);

public:

	bool bIsReplicationSource = false;

	UPROPERTY(BlueprintAssignable)
	FResourcesComponent_OnAnyResourceChanged_Signature OnAnyResourceInitialized;

	UPROPERTY(BlueprintAssignable)
	FResourcesComponent_OnAnyResourceChanged_Signature OnAnyResourceChanged;

	UFUNCTION(BlueprintCallable)
	void SetupResource(const FGameplayTag& InResourceTag, const FResourceInitData& InInitData,
		UResourceInstance*& OutNewResourceInstance);

	UFUNCTION(BlueprintCallable)
	void ConsumeResource(const FGameplayTag& InResourceTag, const float InValue);

	UFUNCTION(BlueprintCallable)
	void AddResource(const FGameplayTag& InResourceTag, const float InValue);

	UFUNCTION(BlueprintPure)
	float GetResourceValue(const FGameplayTag& InResourceTag) const;

	UFUNCTION(BlueprintCallable)
	bool FindResourceInstance(const FGameplayTag& InResourceTag, UResourceInstance*& OutResourceInstance) const;

	UFUNCTION(BlueprintPure)
	static FResourceInitData MakeResourceInitDataFromRepData(const FReplicatedResourceData& InRepData);
	
};
