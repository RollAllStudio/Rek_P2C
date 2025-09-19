// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "DynamicMeshConfig.generated.h"

UCLASS()
class DYNAMICMESHSPAWNER_API UDynamicMeshConfig : public UDataAsset
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintGetter = GetMeshPtr, DisplayName = "Mesh")
	TSoftObjectPtr<UStaticMesh> MeshPtr;

	UPROPERTY(EditAnywhere, BlueprintGetter = GetAttachLocationRule)
	EAttachmentRule AttachLocationRule;

	UPROPERTY(EditAnywhere, BlueprintGetter = GetAttachRotationRule)
	EAttachmentRule AttachRotationRule;

	UPROPERTY(EditAnywhere, BlueprintGetter = GetAttachScaleRule)
	EAttachmentRule AttachScaleRule;

	UPROPERTY(EditAnywhere, BlueprintGetter = GetWeldSimulatedBodies)
	bool bWeldSimulatedBodies = false;

	UPROPERTY(EditAnywhere, BlueprintGetter = GetAttachSocket)
	FName AttachSocket = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintGetter = GetTransformOffset)
	FTransform TransformOffset;

	UPROPERTY(EditAnywhere, BlueprintGetter = GetParentTag)
	FGameplayTag ParentTag;
	
public:

	UFUNCTION(BlueprintGetter)
	TSoftObjectPtr<UStaticMesh> GetMeshPtr() const
	{
		return MeshPtr;
	}

	UFUNCTION(BlueprintGetter)
	EAttachmentRule GetAttachLocationRule() const
	{
		return AttachLocationRule;
	}

	UFUNCTION(BlueprintGetter)
	EAttachmentRule GetAttachRotationRule() const
	{
		return AttachRotationRule;
	}

	UFUNCTION(BlueprintGetter)
	EAttachmentRule GetAttachScaleRule() const
	{
		return AttachScaleRule;
	}

	UFUNCTION(BlueprintGetter)
	FName GetAttachSocket() const
	{
		return AttachSocket;
	}

	UFUNCTION(BlueprintGetter)
	FTransform GetTransformOffset() const
	{
		return TransformOffset;
	}

	UFUNCTION(BlueprintGetter)
	bool GetWeldSimulatedBodies() const
	{
		return bWeldSimulatedBodies;
	}

	UFUNCTION(BlueprintGetter)
	FGameplayTag GetParentTag() const
	{
		return ParentTag;
	}

	FAttachmentTransformRules GetAttachmentRules() const;
	
};
