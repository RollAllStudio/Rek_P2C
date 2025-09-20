// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "DynamicMeshSpawnerComponent.generated.h"


class UDynamicMeshLoader;
class UDynamicMeshConfig;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDynamicMeshSpawnerComponent_OnMeshSpawned_Signature,
	const FGameplayTag&, MeshTag, UStaticMeshComponent*, MeshComponent);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DYNAMICMESHSPAWNER_API UDynamicMeshSpawnerComponent : public UActorComponent
{
	GENERATED_BODY()

	UFUNCTION()
	void OnMeshLoaded(const FGameplayTag& InMeshTag);

	UPROPERTY()
	TMap<FGameplayTag, UDynamicMeshLoader*> MeshLoaders;

	UPROPERTY()
	TMap<FGameplayTag, USceneComponent*> TaggedParents;

	UPROPERTY()
	TMap<FGameplayTag, USceneComponent*> SpawnedComponents;
	
public:

	UPROPERTY(BlueprintAssignable)
	FDynamicMeshSpawnerComponent_OnMeshSpawned_Signature OnMeshSpawned;

	UFUNCTION(BlueprintCallable)
	void LoadAndSpawnMesh(const FGameplayTag& InMeshTag, UDynamicMeshConfig* InMeshConfig);

	UFUNCTION(BlueprintCallable)
	void AddTaggedParent(const FGameplayTag& InTag, USceneComponent* InComponent);

	UFUNCTION(BlueprintCallable)
	bool FindTaggedComponent(const FGameplayTag& InTag, USceneComponent*& OutComponent);
	
};
