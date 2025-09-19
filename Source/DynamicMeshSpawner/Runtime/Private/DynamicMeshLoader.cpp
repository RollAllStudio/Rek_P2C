// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicMeshSpawner/Runtime/Public/DynamicMeshLoader.h"

#include "DynamicMeshSpawner/Config/Public/DynamicMeshConfig.h"

void UDynamicMeshLoader::OnLoadFinished(const FSoftObjectPath& InAssetPath, UObject* InAsset)
{
	LoadedMesh = Cast<UStaticMesh>(InAsset);
	OnMeshLoaded.Broadcast(MeshTag);
}

void UDynamicMeshLoader::LoadFromConfig(const FGameplayTag& InMeshTag, UDynamicMeshConfig* InMeshConfig)
{
	MeshConfig = InMeshConfig;
	MeshTag = InMeshTag;

	if (IsValid(InMeshConfig))
	{
		InMeshConfig->GetMeshPtr().ToSoftObjectPath().LoadAsync(
			FLoadSoftObjectPathAsyncDelegate::CreateUObject(this, &UDynamicMeshLoader::OnLoadFinished));
	}
}
