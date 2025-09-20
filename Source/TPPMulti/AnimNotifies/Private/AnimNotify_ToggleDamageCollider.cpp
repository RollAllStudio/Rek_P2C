// Fill out your copyright notice in the Description page of Project Settings.


#include "..\Public\AnimNotify_ToggleDamageCollider.h"

#include "TPPMulti/Core/MatchPlayer/Public/MatchPlayerCharacter.h"

void UAnimNotify_EnableDamageCollider::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                              const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	AMatchPlayerCharacter* MatchPlayerCharacter = Cast<AMatchPlayerCharacter>(MeshComp->GetOwner());
	if (IsValid(MatchPlayerCharacter))
	{
		if (bEnableDamage)
			MatchPlayerCharacter->EnableMeleeDamage();
		else
			MatchPlayerCharacter->DisableMeleeDamage();
	}
	
}
