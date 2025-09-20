// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellProjectileActor.h"

#include "NiagaraComponent.h"
#include "SpellCasterInterface.h"
#include "SpellConfig.h"
#include "Components/SphereComponent.h"
#include "Engine/OverlapResult.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"


void ASpellProjectileActor::OnRep_SpellConfig()
{
	SetSpellConfig_Internal(SpellConfig);
}

void ASpellProjectileActor::SetSpellConfig_Internal(USpellConfig* InSpellConfig)
{
	SpellConfig = InSpellConfig;
	CollisionComponent->SetCollisionProfileName(InSpellConfig->GetProjectileCollisionProfile());
	FlyNiagaraComponent->SetAsset(InSpellConfig->GetFlyNiagaraSystem());
}

void ASpellProjectileActor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	ProcessHitOrOverlapActor(OtherActor);
}

void ASpellProjectileActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ProcessHitOrOverlapActor(OtherActor);
}

void ASpellProjectileActor::OnHitSystemFinished(UNiagaraComponent* InComponent)
{
	Destroy();
}

void ASpellProjectileActor::ProcessHitOrOverlapActor(AActor* OtherActor)
{
	if (OtherActor != GetOwner())
	{
		SetActorEnableCollision(false);
		if (IsValid(SpellConfig))
		{

			if (SpellConfig->GetDamageRadius() <= 0)
			{
				ApplySpellDamage(OtherActor);
			}
			else
			{
				TArray<FOverlapResult> OverlapResults;
				GetWorld()->OverlapMultiByProfile(OverlapResults, GetActorLocation(), FQuat::Identity,
					SpellConfig->GetHitOverlapProfileName(), FCollisionShape::MakeSphere(SpellConfig->GetDamageRadius()));

			
				for (auto OverlapResult : OverlapResults)
				{
					AActor* HitActor = OverlapResult.GetActor();
					ApplySpellDamage(HitActor);
				}

				HitNiagaraComponent->OnSystemFinished.AddUniqueDynamic(this, &ASpellProjectileActor::OnHitSystemFinished);
				HitNiagaraComponent->SetAsset(SpellConfig->GetHitNiagaraSystem());
			
			}
		
		}

		FlyNiagaraComponent->SetActive(false);
	}
}

void ASpellProjectileActor::ApplySpellDamage(AActor* InActor)
{
	UGameplayStatics::ApplyDamage(InActor, SpellConfig->GetDamage(),
				GetOwner()->GetInstigatorController(),
				USpellCasterInterface::GetSpellInstigatorPawn(GetOwner()),
				SpellConfig->GetDamageType());
}

ASpellProjectileActor::ASpellProjectileActor()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	FlyNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("FlyNiagaraComponent");
	HitNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("HitNiagaraComponent");
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");

	SetRootComponent(CollisionComponent);
	FlyNiagaraComponent->SetupAttachment(CollisionComponent);
	HitNiagaraComponent->SetupAttachment(CollisionComponent);
	ProjectileMovement->SetUpdatedComponent(CollisionComponent);

	ProjectileMovement->ProjectileGravityScale = 0.0f;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->bRotationFollowsVelocity = true;
	
}

void ASpellProjectileActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASpellProjectileActor, SpellConfig)
}

void ASpellProjectileActor::BeginPlay()
{
	Super::BeginPlay();
	SetReplicateMovement(true);
	CollisionComponent->OnComponentHit.AddUniqueDynamic(this, &ASpellProjectileActor::OnHit);
	CollisionComponent->OnComponentBeginOverlap.AddUniqueDynamic(
		this, &ASpellProjectileActor::ASpellProjectileActor::OnBeginOverlap);
}

ASpellProjectileActor* ASpellProjectileActor::SpawnSpellProjectile(AActor* InOwnerActor, USpellConfig* InSpellConfig)
{
	if (IsValid(InOwnerActor))
	{

		ASpellProjectileActor* NewProjectile = InOwnerActor->GetWorld()->SpawnActorDeferred<ASpellProjectileActor>(
			StaticClass(), USpellCasterInterface::GetSpellInitialTransform(InOwnerActor),
			InOwnerActor, USpellCasterInterface::GetSpellInstigatorPawn(InOwnerActor),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		NewProjectile->CollisionComponent->IgnoreActorWhenMoving(InOwnerActor, true);
		NewProjectile->SetSpellConfig_Internal(InSpellConfig);

		NewProjectile->CollisionComponent->SetSphereRadius(InSpellConfig->GetSize());
		NewProjectile->ProjectileMovement->InitialSpeed = InSpellConfig->GetSpeed();
		
		NewProjectile->FinishSpawning(USpellCasterInterface::GetSpellInitialTransform(InOwnerActor));
		return NewProjectile;
		
	}

	return nullptr;
}


