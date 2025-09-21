// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/Pickup/Public/Pickup.h"

#include "Actions/Runtime/Public/ActionsComponent.h"
#include "Components/SphereComponent.h"
#include "TPPMulti/ActionsAPI/Public/ActionsTags.h"

APickup::APickup()
{
	CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
	CollisionComponent->SetupAttachment(GetRootComponent());
	PickupAction = ActionTags::HealthPickup;
}

void APickup::BeginPlay()
{
	Super::BeginPlay();
	CollisionComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &APickup::OnBeginOverlap);
	Hide();
}

void APickup::OnRespawnTimerTimeout()
{
	SetActorEnableCollision(true);
	SetActorHiddenInGame(false);
}

void APickup::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TryOverlapActor(OtherActor);
}

void APickup::TryOverlapActor(AActor* InActor)
{
	UActionsComponent* ActionsComponent =
		InActor->GetComponentByClass<UActionsComponent>();

	if (IsValid(ActionsComponent))
	{
		ActionsComponent->TryExecuteAction(PickupAction);
		Hide();
	}
	
}

void APickup::Hide()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	GetWorld()->GetTimerManager().SetTimer(RespawnTimer, FTimerDelegate::CreateUObject(this,
		&APickup::OnRespawnTimerTimeout), RespawnTime, false);
}
