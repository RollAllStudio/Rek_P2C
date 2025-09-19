// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellConfig.h"

FName USpellConfig::GetProjectileCollisionProfile() const
{
	return ProjectileCollisionProfile.Name;
}

FName USpellConfig::GetHitOverlapProfileName() const
{
	return HitOverlapProfileName.Name;
}
