// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPPMulti/CharactersDataBase/Public/CharactersDataBase.h"
#include "MatchPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class TPPMULTI_API AMatchPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

#pragma region Core
	
	UPROPERTY(VisibleAnywhere, Category = Components)
	USpringArmComponent* CameraBoomComponent;

	UPROPERTY(VisibleAnywhere, Category = Components)
	USceneComponent* MeshRootComponent;	

	UPROPERTY(VisibleAnywhere, Category = Components)
	UCameraComponent* CameraComponent;

	UFUNCTION()
	void OnServerUIDChanged(const int32& InNewUID);
	void InitWithPlayerState();

public:

	AMatchPlayerCharacter();

protected:
	
	virtual void BeginPlay() override;
	virtual void OnRep_PlayerState() override;
	virtual void OnPlayerStateChanged(APlayerState* NewPlayerState, APlayerState* OldPlayerState) override;

#pragma endregion 
	
#pragma region CharacterData

private:

	UPROPERTY(BlueprintGetter = GetCharacterData)
	FCharacterData CharacterData;
	
	UFUNCTION()
	void OnCharacterMeshLoaded(const FSoftObjectPath& InAssetPath, UObject* InAsset);

public:

	UFUNCTION(BlueprintGetter)
	FCharacterData GetCharacterData() const
	{
		return CharacterData;
	}

	UFUNCTION(BlueprintCallable)
	void LoadCharacterData(const FDataTableRowHandle& InDataRow);
	
#pragma endregion 
	
};

