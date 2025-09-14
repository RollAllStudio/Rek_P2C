// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MultiplayerGame/Server/Public/ServerPlayerState.h"
#include "LobbyPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLobbyPlayerState_IsReadyChanged_Signature, const bool, Value);

UCLASS()
class TPPMULTI_API ALobbyPlayerState : public AServerPlayerState
{
	GENERATED_BODY()

	UPROPERTY(BlueprintGetter = GetIsReady, BlueprintSetter = SetIsReady, ReplicatedUsing = OnRep_IsReady)
	bool bIsReady = false;

	UFUNCTION()
	void OnRep_IsReady();
	void SetIsReadyInternal(const bool InNewIsReady);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SetIsReady(const bool InNewIsReady);

public:

	UPROPERTY(BlueprintAssignable)
	FLobbyPlayerState_IsReadyChanged_Signature OnIsReadyChanged;

	UFUNCTION(BlueprintGetter)
	bool GetIsReady() const
	{
		return bIsReady;
	}

	UFUNCTION(BlueprintSetter)
	void SetIsReady(const bool InNewIsReady);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
};
