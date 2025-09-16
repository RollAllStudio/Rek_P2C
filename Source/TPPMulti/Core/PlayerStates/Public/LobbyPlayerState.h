// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MultiplayerGame/Server/Public/ServerPlayerState.h"
#include "LobbyPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLobbyPlayerState_IsReadyChanged_Signature, const bool, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLobbyPlayerState_OnCharacterRowChanged_Signature,
	const FDataTableRowHandle&, NewRow);

UCLASS()
class TPPMULTI_API ALobbyPlayerState : public AServerPlayerState
{
	GENERATED_BODY()

#pragma region IsReady
	
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

#pragma endregion 

#pragma region CharacterRow

private:
	
	UPROPERTY(ReplicatedUsing = OnRep_CharacterRow)
	FDataTableRowHandle CharacterRow;

	UFUNCTION()
	void OnRep_CharacterRow();

	void SetCharacterRow_Internal(const FDataTableRowHandle& InCharacterRow);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SetCharacterRow(const FDataTableRowHandle& InCharacterRow);
	
public:

	UFUNCTION(BlueprintGetter)
	FDataTableRowHandle GetCharacterRow() const
	{
		return CharacterRow;
	}
	
	UFUNCTION(BlueprintSetter)
	void SetCharacterRow(const FDataTableRowHandle& InCharacterRow);
	
	UPROPERTY(BlueprintAssignable)
	FLobbyPlayerState_OnCharacterRowChanged_Signature OnCharacterRowChanged;
	
#pragma endregion 

public:
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
};
