// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ResourceDataTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CharactersDataBase.generated.h"


class UDynamicMeshConfig;
class UActionsCollection;

USTRUCT(BlueprintType)
struct FCharacterData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	TSoftObjectPtr<USkeletalMesh> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FTransform MeshOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	TSubclassOf<UAnimInstance> AnimInstance;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	TSoftObjectPtr<UActionsCollection> ActionsCollection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	TMap<FGameplayTag, UDynamicMeshConfig*> DynamicMeshes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FName SpellSpawnSocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	TMap<FGameplayTag, FResourceInitData> ResourcesData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	FSlateBrush DisplayImage;
	
};

UCLASS()
class TPPMULTI_API UCharactersDataBase : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	static bool ReadCharacterData(const FDataTableRowHandle& InRowHandle, FCharacterData& OutData);
	
};
