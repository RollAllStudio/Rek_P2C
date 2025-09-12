// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MultiplayerGameSubsystem.generated.h"

#define SESSION_SETTING_NAME_SESSION_NAME FName("SessionName")

class USessionsFindResult;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMultiplayerGameSubsystem_EmptyEvent_Singature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerGameSubsystem_TextEvent_Signature, const FText&, NewText);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerGameSubsystem_BoolEvent_Signature, const bool, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerGameSubsystem_SessionsFindComplete_Signature,
	USessionsFindResult*, SessionsFindPtr);

UCLASS()
class MULTIPLAYERGAME_API UMultiplayerGameSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, meta=(WorldContext = WorldContextObject))
	static UMultiplayerGameSubsystem* GetSubsystem(const UObject* WorldContextObject);

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

#pragma region LocalData

private:
	
	UPROPERTY()
	FText LocalHostedSessionName;

	UPROPERTY()
	FText LocalJoinedSessionName;

	UPROPERTY()
	bool bIsHost;

	UPROPERTY()
	FText LocalPlayerName;

	UPROPERTY()
	bool bCanHostSession;

	void SetLocalSessionName_Internal(const FText& InNewSessionName);
	void SetLocalPlayerName_Internal(const FText& InNewPlayerName);
	void OnHostConditionsChanged();

public:

	UFUNCTION(BlueprintCallable, Category = "MultiplayerGame|LocalData", meta=(WorldContext = WorldContextObject))
	static void SetLocalHostedSessionName(const FText& InNewSessionName, const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "MultiplayerGame|LocalData", meta=(WorldContext = WorldContextObject))
	static FText GetLocalHostedSessionName(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "MultiplayerGame|LocalData", meta=(WorldContext = WorldContextObject))
	static void SetLocalPlayerName(const UObject* WorldContextObject, const FText& InNewName);

	UFUNCTION(BlueprintPure, Category = "MultiplayerGame|LocalData", meta=(WorldContext = WorldContextObject))
	static FText GetLocalPlayerName(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "MultiplayerGame|LocalData", meta=(WorldContext = WorldContextObject))
	static bool CanHostSession(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintPure, Category = "MultiplayerGame|LocalData", meta=(WorldContext = WorldContextObject))
	static FText GetLocalJoinedSessionName(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "MultiplayerGame|LocalData", meta=(WorldContext = WorldContextObject))
	static bool IsHost(const UObject* WorldContextObject);
	
	UPROPERTY(BlueprintAssignable)
	FMultiplayerGameSubsystem_TextEvent_Signature OnLocalSessionNameChanged;

	UPROPERTY(BlueprintAssignable)
	FMultiplayerGameSubsystem_TextEvent_Signature OnLocalPlayerNameChanged;

	UPROPERTY(BlueprintAssignable)
	FMultiplayerGameSubsystem_BoolEvent_Signature OnCanHostSessionChanged;
	
#pragma endregion

#pragma region SessionManager

private:

	FString CreateServerTravelLink(const FString& InWorldPath);

	IOnlineSessionPtr OnlineSessionsPtr;
	TSharedPtr<FOnlineSessionSearch> SessionSearchPtr;
	bool bLoopingFindSessions = false;
	bool bIsLookingForSessions = false;
	
	void CreateSession_Internal(const TMap<FName, FString>& InSessionSettings);
	void CloseSession_Internal();
	void StartFindSessionsLoop_Internal();
	void StopFindSessionsLoop_Internal();
	void StartNextFindSessions();
	void JoinSessionByIndex_Internal(const int32& InSessionIndex);

	UFUNCTION()
	void OnSessionCreated(FName InSessionName, bool InWasSuccessful);

	UFUNCTION()
	void OnSessionSearchComplete(bool InWasSuccessful);

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	
public:

	UPROPERTY(BlueprintAssignable)
	FMultiplayerGameSubsystem_SessionsFindComplete_Signature OnSessionsFindComplete;

	UPROPERTY(BlueprintAssignable)
	FMultiplayerGameSubsystem_EmptyEvent_Singature OnStartJoiningSession;

	UFUNCTION(BlueprintCallable, Category = "MultiplayerGame|Sessions", meta=(WorldContext = WorldContextObject))
	static void CreateSession(const TMap<FName, FString>& InSessionSettings, const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "MultiplayerGame|Sessions", meta=(WorldContext = WorldContextObject))
	static void CloseSession(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "MultiplayerGame|Sessions", meta=(WorldContext = WorldContextObject))
	static void StartFindSessionsLoop(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "MultiplayerGame|Sessions", meta=(WorldContext = WorldContextObject))
	static void StopFindSessionsLoop(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "MultiplayerGame|Sessions", meta=(WorldContext = WorldContextObject))
	static void JoinSessionByIndex(const UObject* WorldContextObject, const int32& InSessionIndex);	
	
#pragma endregion 
	
};

