// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ServerPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FServerPlayerState_ServerPlayerNameChanged, const FString&, NewName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FServerPlayerState_ServerUIDChanged, const int32&, NewUID);

UCLASS()
class MULTIPLAYERGAME_API AServerPlayerState : public APlayerState
{
	GENERATED_BODY()

private:

	UPROPERTY(BlueprintGetter = GetServerPlayerName, BlueprintSetter = SetServerPlayerName, ReplicatedUsing = OnRep_ServerPlayerName)
	FString ServerPlayerName;

	UPROPERTY(BlueprintGetter = GetServerUID, BlueprintSetter = SetServerUID, ReplicatedUsing = OnRep_ServerUID)
	int32 ServerUID = INDEX_NONE;

	UFUNCTION()
	void OnRep_ServerPlayerName();

	UFUNCTION()
	void OnRep_ServerUID();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_ShareServerUID(const int32& InServerUID);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_ShareServerName(const FString& InServerName);

	void SetServerPlayerName_Internal(const FString& InNewName);
	void SetServerUID_Internal(const int32& InNewUID);
	
public:

	UPROPERTY(BlueprintAssignable)
	FServerPlayerState_ServerPlayerNameChanged OnServerNameChanged;

	UPROPERTY(BlueprintAssignable)
	FServerPlayerState_ServerUIDChanged OnServerUIDChanged;

	UFUNCTION(BlueprintGetter)
	FString GetServerPlayerName() const
	{
		return ServerPlayerName;
	}

	UFUNCTION(BlueprintSetter)
	void SetServerPlayerName(const FString& InNewName);

	UFUNCTION(BlueprintGetter)
	int32 GetServerUID() const
	{
		return ServerUID;
	}

	UFUNCTION(BlueprintSetter)
	void SetServerUID(const int32& InServerUID);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
};
