// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MultiplayerGameSubsystem.generated.h"

#define SESSION_SETTING_NAME_SESSION_NAME FName("SessionName")

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerGameSubsystem_TextEvent, const FText&, NewText);

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
	FText LocalSessionName;

	void SetLocalSessionName_Internal(const FText& InNewSessionName);

public:

	UFUNCTION(BlueprintCallable, Category = "MultiplayerGame|LocalData", meta=(WorldContext = WorldContextObject))
	static void SetLocalSessionName(const FText& InNewSessionName, const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "MultiplayerGame|LocalData", meta=(WorldContext = WorldContextObject))
	static FText GetLocalSessionName(const UObject* WorldContextObject);

	UPROPERTY(BlueprintAssignable)
	FMultiplayerGameSubsystem_TextEvent OnLocalSessionNameChanged;
	
#pragma endregion

#pragma region SessionManager

private:

	FString CreateServerTravelLink(const FString& InWorldPath);

	IOnlineSessionPtr OnlineSessionPtr;
	void CreateSession_Internal(const TMap<FName, FString>& InSessionSettings);
	void CloseSession_Internal();

	UFUNCTION()
	void OnSessionCreated(FName InSessionName, bool InWasSuccessful);
	
public:

	UFUNCTION(BlueprintCallable, Category = "MultiplayerGame|Sessions", meta=(WorldContext = WorldContextObject))
	static void CreateSession(const TMap<FName, FString>& InSessionSettings, const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "MultiplayerGame|Sessions", meta=(WorldContext = WorldContextObject))
	static void CloseSession(const UObject* WorldContextObject);
	
#pragma endregion 
	
};

