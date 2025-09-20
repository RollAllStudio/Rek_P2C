// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "MeleeDamageColliderComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TPPMULTI_API UMeleeDamageColliderComponent : public UCapsuleComponent
{
	GENERATED_BODY()

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY()
	TArray<AActor*> DamagedActors;

	UPROPERTY()
	TArray<AActor*> OverlappedActors;

	bool bDamaging = false;

	void TryDamageActor(AActor* InActor);
	void AddOverlappedActor(AActor* InActor);
	void RemoveOverlappedActor(AActor* InActor);
	
	UPROPERTY(BlueprintGetter = GetDamage, BlueprintSetter = SetDamage)
	float Damage;

	UPROPERTY(BlueprintGetter = GetDamageType, BlueprintSetter = SetDamageType)
	TSubclassOf<UDamageType> DamageType;
	
protected:
	
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintGetter)
	float GetDamage() const
	{
		return Damage;
	}
	
	UFUNCTION(BlueprintSetter)
	void SetDamage(const float InDamage);

	UFUNCTION(BlueprintGetter)
	TSubclassOf<UDamageType> GetDamageType() const
	{
		return DamageType;
	}

	UFUNCTION(BlueprintSetter)
	void SetDamageType(const TSubclassOf<UDamageType>& InDamageType);

	UFUNCTION(BlueprintCallable)
	void StartDamaging();

	UFUNCTION(BlueprintCallable)
	void StopDamaging();
};

