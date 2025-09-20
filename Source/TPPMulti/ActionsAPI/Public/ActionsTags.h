// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace ActionTags
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(PrimaryAction)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Death)
}

namespace ActionStackTags
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(PlayerInput)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(GlobalStack)
}
