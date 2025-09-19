// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/Runtime/Public/ActionsComponent.h"
#include "Actions/Config/ActionDefinitions/Public/ActionDefinition_Base.h"
#include "Actions/Config/ActionsCollection/Public/ActionsCollection.h"
#include "Actions/Runtime/Public/ActionsStackInstance.h"


bool UActionsComponent::IsStackLocked(const FGameplayTag& InStackTag)
{
	if (ActionStacks.Contains(InStackTag))
		return ActionStacks[InStackTag]->IsLocked();

	return false;
}

void UActionsComponent::LockStack(const FGameplayTag& InStackTag, const float InDuration)
{
	if (ActionStacks.Contains(InStackTag))
	{
		ActionStacks[InStackTag]->Lock(this, InDuration);
		return;
	}

	UActionsStackInstance* NewStackInstance = NewObject<UActionsStackInstance>(this);
	NewStackInstance->Lock(this, InDuration);
	ActionStacks.Add(InStackTag, NewStackInstance);
}

void UActionsComponent::UnlockStack(const FGameplayTag& InStackTag)
{
	if (ActionStacks.Contains(InStackTag))
		ActionStacks[InStackTag]->Unlock(this);
}

void UActionsComponent::TryExecuteAction(const FGameplayTag& InActionTag)
{
	UActionDefinition_Base* ActionDefinition;
	if (IsValid(ActionsCollections))
		if (ActionsCollections->FindActionByTag(InActionTag, ActionDefinition))
			ActionDefinition->ExecuteAction(this);
}

void UActionsComponent::OnActionsCollectionLoaded(const FSoftObjectPath& InAssetPath, UObject* InAsset)
{
	if (RequestedCollectionRef == InAssetPath)
		ActionsCollections = Cast<UActionsCollection>(InAsset);
}

void UActionsComponent::LoadActionsCollection(const TSoftObjectPtr<UActionsCollection>& InActionsCollection)
{

	RequestedCollectionRef = InActionsCollection.ToSoftObjectPath();
	RequestedCollectionRef.LoadAsync(FLoadSoftObjectPathAsyncDelegate::CreateUObject(this,
		&UActionsComponent::OnActionsCollectionLoaded));
	
}
