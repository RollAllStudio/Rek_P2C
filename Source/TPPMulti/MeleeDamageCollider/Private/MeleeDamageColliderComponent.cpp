// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/MeleeDamageCollider/Public/MeleeDamageColliderComponent.h"

#include "Kismet/GameplayStatics.h"


void UMeleeDamageColliderComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AddOverlappedActor(OtherActor);
}

void UMeleeDamageColliderComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	RemoveOverlappedActor(OtherActor);
}

void UMeleeDamageColliderComponent::TryDamageActor(AActor* InActor)
{
	if (InActor != GetOwner() && !DamagedActors.Contains(InActor))
	{
		DamagedActors.Add(InActor);
		UGameplayStatics::ApplyDamage(InActor, Damage, GetOwner()->GetInstigatorController(), GetOwner(),
			DamageType);
	}
}

void UMeleeDamageColliderComponent::AddOverlappedActor(AActor* InActor)
{
	OverlappedActors.Add(InActor);
	if (bDamaging)
		TryDamageActor(InActor);
}

void UMeleeDamageColliderComponent::RemoveOverlappedActor(AActor* InActor)
{
	OverlappedActors.Remove(InActor);
}

void UMeleeDamageColliderComponent::BeginPlay()
{
	Super::BeginPlay();
	OnComponentBeginOverlap.AddUniqueDynamic(this, &UMeleeDamageColliderComponent::OnBeginOverlap);
	OnComponentEndOverlap.AddUniqueDynamic(this, &UMeleeDamageColliderComponent::OnEndOverlap);
}

void UMeleeDamageColliderComponent::SetDamage(const float InDamage)
{
	Damage = InDamage;
}

void UMeleeDamageColliderComponent::SetDamageType(const TSubclassOf<UDamageType>& InDamageType)
{
	DamageType = InDamageType;
}

void UMeleeDamageColliderComponent::StartDamaging()
{
	bDamaging = true;
	for (auto OverlappedActor : OverlappedActors)
		TryDamageActor(OverlappedActor);
}

void UMeleeDamageColliderComponent::StopDamaging()
{
	bDamaging = false;
	DamagedActors.Empty();
}



