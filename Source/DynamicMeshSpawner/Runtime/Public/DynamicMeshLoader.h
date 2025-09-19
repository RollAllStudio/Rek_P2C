// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "DynamicMeshLoader.generated.h"

class UDynamicMeshConfig;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDynamicMeshLoader_OnMeshLoaded_Signature,
                                            const FGameplayTag&, MeshTag);

UCLASS()
class DYNAMICMESHSPAWNER_API UDynamicMeshLoader : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
	UDynamicMeshConfig* MeshConfig;
	FGameplayTag MeshTag;

	UPROPERTY()
	UStaticMesh* LoadedMesh;
	
	void OnLoadFinished(const FSoftObjectPath& InAssetPath, UObject* InAsset);

public:

	UPROPERTY(BlueprintAssignable)
	FDynamicMeshLoader_OnMeshLoaded_Signature OnMeshLoaded;

	void LoadFromConfig(const FGameplayTag& InMeshTag, UDynamicMeshConfig* InMeshConfig);
	UDynamicMeshConfig* GetMeshConfig() const
	{
		return MeshConfig;
	}

	UStaticMesh* GetLoadedMesh() const
	{
		return LoadedMesh;
	}
	
};
