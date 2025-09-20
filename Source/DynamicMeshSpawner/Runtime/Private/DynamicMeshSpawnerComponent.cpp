// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicMeshSpawner/Runtime/Public/DynamicMeshSpawnerComponent.h"
#include "DynamicMeshSpawner/Config/Public/DynamicMeshConfig.h"
#include "DynamicMeshSpawner/Runtime/Public/DynamicMeshLoader.h"


void UDynamicMeshSpawnerComponent::OnMeshLoaded(const FGameplayTag& InMeshTag)
{

	UStaticMesh* StaticMesh = MeshLoaders[InMeshTag]->GetLoadedMesh();
	UDynamicMeshConfig* MeshConfig = MeshLoaders[InMeshTag]->GetMeshConfig();

	UStaticMeshComponent* NewComponent = NewObject<UStaticMeshComponent>(GetOwner());
	NewComponent->RegisterComponent();
	NewComponent->SetStaticMesh(StaticMesh);

	USceneComponent* ParentComponent;
	if (MeshConfig->GetParentTag().IsValid())
	{
		FindTaggedComponent(MeshConfig->GetParentTag(), ParentComponent);
	}
	else
	{
		ParentComponent = GetOwner()->GetRootComponent();
	}

	NewComponent->AttachToComponent(ParentComponent, MeshConfig->GetAttachmentRules(), MeshConfig->GetAttachSocket());
	NewComponent->SetRelativeTransform(MeshConfig->GetTransformOffset());
	SpawnedComponents.Add(InMeshTag, NewComponent);
	OnMeshSpawned.Broadcast(InMeshTag, NewComponent);
}

void UDynamicMeshSpawnerComponent::LoadAndSpawnMesh(const FGameplayTag& InMeshTag, UDynamicMeshConfig* InMeshConfig)
{
	UDynamicMeshLoader* MeshLoader = NewObject<UDynamicMeshLoader>(this);
	MeshLoader->OnMeshLoaded.AddUniqueDynamic(this, &UDynamicMeshSpawnerComponent::OnMeshLoaded);
	MeshLoaders.Add(InMeshTag, MeshLoader);
	MeshLoader->LoadFromConfig(InMeshTag, InMeshConfig);
}

void UDynamicMeshSpawnerComponent::AddTaggedParent(const FGameplayTag& InTag, USceneComponent* InComponent)
{
	TaggedParents.Add(InTag, InComponent);
}

bool UDynamicMeshSpawnerComponent::FindTaggedComponent(const FGameplayTag& InTag, USceneComponent*& OutComponent)
{
	if (TaggedParents.Contains(InTag))
	{
		OutComponent = TaggedParents[InTag];
		return true;
	}

	if (SpawnedComponents.Contains(InTag))
	{
		OutComponent = SpawnedComponents[InTag];
		return true;
	}

	return false;
}
