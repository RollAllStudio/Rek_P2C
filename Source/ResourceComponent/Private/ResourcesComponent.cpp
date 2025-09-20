// Fill out your copyright notice in the Description page of Project Settings.


#include "..\Public\ResourcesComponent.h"
#include "ResourceInstance.h"
#include "Net/UnrealNetwork.h"

void UResourcesComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UResourcesComponent, ResourcesRepData)
}

void UResourcesComponent::UpdateReplicatedResource(const FGameplayTag& InResourceTag,
                                                   UResourceInstance* InResourceInstance)
{
#define UPDATE_REP_VALUE(Value, Getter) ResourcesRepData[IndexToUpdate]. Value = InResourceInstance-> Getter ;

	int32 IndexToUpdate = INDEX_NONE;
	for (int32 i = 0; i < ResourcesRepData.Num(); i++)
	{
		FReplicatedResourceData LocalData = ResourcesRepData[i];
		if (LocalData.ResourceTag == InResourceTag)
		{
			IndexToUpdate = i;
			break;
		}
	}

	if (IndexToUpdate == INDEX_NONE)
	{
		FReplicatedResourceData NewRepData;
		NewRepData.ResourceTag = InResourceTag;
		IndexToUpdate = ResourcesRepData.Add(NewRepData);
	}

	UPDATE_REP_VALUE(CurrentValue, GetCurrentValue())
	UPDATE_REP_VALUE(MaxValue, GetMaxValue())
	UPDATE_REP_VALUE(RegenSpeed, GetRegenSpeed())
	UPDATE_REP_VALUE(bDepleted, GetIsDepleted())
	UPDATE_REP_VALUE(bCanRegenWhenDepleted, GetCanRegenWhenDepleted())
	
#undef UPDATE_REP_VALUE
}

void UResourcesComponent::UpdateLocalResource(const FGameplayTag& InResourceTag,
	const FReplicatedResourceData& InResourceData)
{
	UResourceInstance* ResourceInstance;
	if (FindResourceInstance(InResourceTag, ResourceInstance))
	{
		ResourceInstance->UpdateWithRepData(InResourceData);
	}
	else
	{
		SetupResource(InResourceTag, MakeResourceInitDataFromRepData(InResourceData), ResourceInstance);
		ResourceInstance->UpdateWithRepData(InResourceData);
	}
}

void UResourcesComponent::OnRep_ResourcesData()
{
	for (auto LocalRepData : ResourcesRepData) 
		UpdateLocalResource(LocalRepData.ResourceTag, LocalRepData);
}

#define UPDATE_REPLICATED_RESOURCE(ResourceTag, ResourceInstance) \
	if (bIsReplicationSource) UpdateReplicatedResource( ResourceTag , ResourceInstance ); \
	OnAnyResourceChanged.Broadcast( ResourceTag );

void UResourcesComponent::OnResourceChanged(const FGameplayTag& InResourceTag, UResourceInstance* InResourceInstance,
	const float InOldValue, const float InNewValue)
{
	UPDATE_REPLICATED_RESOURCE(InResourceTag, InResourceInstance)
}

void UResourcesComponent::OnResourceDepleted(const FGameplayTag& InResourceTag, UResourceInstance* InResourceInstance)
{
	UPDATE_REPLICATED_RESOURCE(InResourceTag, InResourceInstance)
}

#undef UPDATE_REPLICATED_RESOURCE

void UResourcesComponent::SetupResource(const FGameplayTag& InResourceTag, const FResourceInitData& InInitData,
                                        UResourceInstance*& OutNewResourceInstance)
{
	UResourceInstance* NewResourceInstance = NewObject<UResourceInstance>(this);
	NewResourceInstance->OnResourceChanged_Signature.AddUniqueDynamic(this, &UResourcesComponent::OnResourceChanged);
	NewResourceInstance->OnResourceDepleted.AddUniqueDynamic(this, &UResourcesComponent::OnResourceDepleted);
	NewResourceInstance->Setup(InResourceTag, InInitData);
	ResourceInstances.Add(InResourceTag, NewResourceInstance);
	OutNewResourceInstance = NewResourceInstance;
	OnAnyResourceInitialized.Broadcast(InResourceTag);
}

#define CALL_ON_RESOURCE(ResourceTag, Function, Param) \
	UResourceInstance* ResourceInstance; if (FindResourceInstance( ResourceTag , ResourceInstance)) \
	ResourceInstance-> Function ( Param );


void UResourcesComponent::ConsumeResource(const FGameplayTag& InResourceTag, const float InValue)
{
	CALL_ON_RESOURCE(InResourceTag, ConsumeResource, InValue)
}

void UResourcesComponent::AddResource(const FGameplayTag& InResourceTag, const float InValue)
{
	CALL_ON_RESOURCE(InResourceTag, AddResource, InValue)
}

#undef CALL_ON_RESOURCE

float UResourcesComponent::GetResourceValue(const FGameplayTag& InResourceTag) const
{
	UResourceInstance* ResourceInstance;
	if (FindResourceInstance(InResourceTag , ResourceInstance))
		return ResourceInstance->GetCurrentValue();
	return 0.0f;
}

bool UResourcesComponent::FindResourceInstance(const FGameplayTag& InResourceTag,
	UResourceInstance*& OutResourceInstance) const
{
	if (ResourceInstances.Contains(InResourceTag))
	{
		OutResourceInstance = ResourceInstances[InResourceTag];
		return IsValid(OutResourceInstance);
	}
	return false;
}

FResourceInitData UResourcesComponent::MakeResourceInitDataFromRepData(const FReplicatedResourceData& InRepData)
{
	FResourceInitData OutData;
	OutData.InitValue = InRepData.MaxValue;
	OutData.RegenSpeed = InRepData.RegenSpeed;
	OutData.bCanRegenWhenDepleted = InRepData.bCanRegenWhenDepleted;
	return OutData;
}
