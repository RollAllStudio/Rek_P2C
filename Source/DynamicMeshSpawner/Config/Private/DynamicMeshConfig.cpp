// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicMeshSpawner/Config/Public/DynamicMeshConfig.h"

FAttachmentTransformRules UDynamicMeshConfig::GetAttachmentRules() const
{
	return FAttachmentTransformRules(AttachLocationRule, AttachRotationRule, AttachScaleRule, bWeldSimulatedBodies);
}
