// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ServerPlayerData.h"
#include "GameFramework/PlayerController.h"
#include "ServerPlayerController.generated.h"

class UServerPlayerData;
class AServerPlayerState;
/**
 * 
 */
UCLASS()
class MULTIPLAYERGAME_API AServerPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	UPROPERTY(ReplicatedUsing = OnRep_ServerUID, BlueprintGetter = GetServerUID)
	int32 ServerUID = INDEX_NONE;

	bool bServerPawnInitialized = false;

	UFUNCTION()
	void OnRep_ServerUID();
	void SetServerUID_Internal(const int32& InNewUID);

	void SetupServerPlayerState() const;
	
public:

	virtual void InitPlayerState() override;
	virtual void OnRep_PlayerState() override;

	UFUNCTION(Client, Reliable)
	void Client_LeaveSession();

	UFUNCTION(Client, Reliable)
	void Client_LoginServerPlayer();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_LoginServerPlayer(const int32& InServerPlayerUID);

	UFUNCTION(BlueprintGetter)
	int32 GetServerUID() const
	{
		return ServerUID;
	}
	
	UFUNCTION(BlueprintPure)
	AServerPlayerState* GetServerPlayerState() const;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
};
