// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpellProjectileActor.generated.h"

class UNiagaraComponent;
class UProjectileMovementComponent;
class USphereComponent;
class USpellConfig;

UCLASS()
class SPELLPROJECTILE_API ASpellProjectileActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UNiagaraComponent* FlyNiagaraComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UNiagaraComponent* HitNiagaraComponent;
	
	UPROPERTY(ReplicatedUsing = OnRep_SpellConfig)
	USpellConfig* SpellConfig = nullptr;

	UFUNCTION()
	void OnRep_SpellConfig();
	void SetSpellConfig_Internal(USpellConfig* InSpellConfig);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
			   UPrimitiveComponent* OtherComp, FVector NormalImpulse,
			   const FHitResult& Hit);

	UFUNCTION()
	void OnHitSystemFinished(UNiagaraComponent* InComponent);

	void ApplySpellDamage(AActor* InActor);

public:
	
	ASpellProjectileActor();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:

	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable)
	static ASpellProjectileActor* SpawnSpellProjectile(AActor* InOwnerActor, USpellConfig* InSpellConfig);
	
};
