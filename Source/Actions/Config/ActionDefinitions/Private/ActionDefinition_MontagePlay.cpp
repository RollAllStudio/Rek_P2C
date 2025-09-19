// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/Config/ActionDefinitions/Public/ActionDefinition_MontagePlay.h"
#include "Actions/Runtime/Public/ActionsComponent.h"
#include "GameFramework/Character.h"

TArray<FName> UActionDefinition_MontagePlay::GetSelectedMontageSections() const
{

	TArray<FName> ReturnBuffer;
	if (IsValid(MontageToPlay))
		for (auto Section : MontageToPlay->CompositeSections)
			ReturnBuffer.Add(Section.SectionName);

	return ReturnBuffer;
	
}

float UActionDefinition_MontagePlay::ExecuteAction_Internal(UActionsComponent* InActionsComponent)
{
	const ACharacter* Character = Cast<ACharacter>(InActionsComponent->GetOwner());
	if (IsValid(Character))
	{
		const USkeletalMeshComponent* CharacterMesh = Character->GetMesh();
		const float MontageLen = CharacterMesh->GetAnimInstance()->Montage_Play(MontageToPlay, PlayRate);
		return MontageLen;
	}

	return -1;
}

