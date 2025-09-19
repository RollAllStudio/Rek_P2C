// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/AnimNotifies/Public/AnimNotify_SpawnSpellProjectile.h"

#include "MultiplayerGameSubsystem.h"
#include "SpellProjectileActor.h"

UAnimNotify_SpawnSpellProjectile::UAnimNotify_SpawnSpellProjectile()
{
	bShouldFireInEditor = false;
}

void UAnimNotify_SpawnSpellProjectile::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                              const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (UMultiplayerGameSubsystem::IsHost(MeshComp))
		ASpellProjectileActor::SpawnSpellProjectile(MeshComp->GetOwner(), SpellConfig);
}
