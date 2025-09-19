// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/ActionsTags/Public/ActionsTags.h"

namespace ActionTags
{
	UE_DEFINE_GAMEPLAY_TAG(PrimaryAction, "Actions.PrimaryAction")
	UE_DEFINE_GAMEPLAY_TAG(Death, "Actions.Death")
}

namespace ActionStackTags
{
	UE_DEFINE_GAMEPLAY_TAG(PlayerInput, "ActionStacks.PlayerInput")
	UE_DEFINE_GAMEPLAY_TAG(GlobalStack, "ActionStacks.Global")
}
