// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

class USphereComponent;

UCLASS()
class TPPMULTI_API APickup : public AStaticMeshActor
{
	GENERATED_BODY()

public:

	APickup();

protected:

	virtual void BeginPlay() override;
	
private:
	
	UPROPERTY(EditInstanceOnly)
	FGameplayTag PickupAction;

	UPROPERTY(VisibleAnywhere, Category = Components)
	USphereComponent* CollisionComponent;

	UPROPERTY(EditInstanceOnly)
	float RespawnTime = 25.0f;

	UPROPERTY()
	FTimerHandle RespawnTimer;

	UFUNCTION()
	void OnRespawnTimerTimeout();

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void TryOverlapActor(AActor* InActor);
	void Hide();
	
};
