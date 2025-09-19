// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SpellConfig.generated.h"

class UNiagaraSystem;
/**
 * 
 */
UCLASS()
class SPELLPROJECTILE_API USpellConfig : public UDataAsset
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintGetter = GetFlyNiagaraSystem)
	UNiagaraSystem* FlyNiagaraSystem;

	UPROPERTY(EditAnywhere, BlueprintGetter = GetHitNiagaraSystem)
	UNiagaraSystem* HitNiagaraSystem;
	
	UPROPERTY(EditAnywhere, BlueprintGetter = GetSpeed)
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintGetter = GetSize)
	float Size;

	UPROPERTY(EditAnywhere, BlueprintGetter = GetDamage)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintGetter = GetDamageRadius)
	float DamageRadius;

	UPROPERTY(EditAnywhere, BlueprintGetter = GetDamageType)
	TSubclassOf<UDamageType> DamageType;
	
	UPROPERTY(EditAnywhere)
	FCollisionProfileName ProjectileCollisionProfile;

	UPROPERTY(EditAnywhere)
	FCollisionProfileName HitOverlapProfileName;
	
public:

	UFUNCTION(BlueprintGetter)
	UNiagaraSystem* GetFlyNiagaraSystem() const
	{
		return FlyNiagaraSystem;
	}

	UFUNCTION(BlueprintGetter)
	UNiagaraSystem* GetHitNiagaraSystem() const
	{
		return HitNiagaraSystem;
	}

	UFUNCTION(BlueprintGetter)
	float GetSpeed() const
	{
		return Speed;
	}

	UFUNCTION(BlueprintGetter)
	float GetSize() const
	{
		return Size;
	}

	UFUNCTION(BlueprintGetter)
	float GetDamage() const
	{
		return Damage;
	}

	UFUNCTION(BlueprintGetter)
	float GetDamageRadius() const
	{
		return DamageRadius;
	}

	UFUNCTION(BlueprintGetter)
	TSubclassOf<UDamageType> GetDamageType() const
	{
		return DamageType;
	}

	UFUNCTION(BlueprintPure)
	FName GetProjectileCollisionProfile() const;

	UFUNCTION(BlueprintPure)
	FName GetHitOverlapProfileName() const;
	
};
