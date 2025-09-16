// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MatchPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class TPPMULTI_API AMatchPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = Components)
	USpringArmComponent* CameraBoomComponent;

	UPROPERTY(VisibleAnywhere, Category = Components)
	UCameraComponent* CameraComponent;	

public:

	AMatchPlayerCharacter();

protected:
	
	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void OnCharacterMeshLoaded(const FSoftObjectPath& InAssetPath, UObject* InAsset);
	
};
