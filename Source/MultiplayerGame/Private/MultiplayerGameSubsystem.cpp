// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerGameSubsystem.h"

#include "MultiplayerGameConstants.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Kismet/GameplayStatics.h"

UMultiplayerGameSubsystem* UMultiplayerGameSubsystem::GetSubsystem(const UObject* WorldContextObject)
{
	return UGameplayStatics::GetGameInstance(WorldContextObject)->GetSubsystem<UMultiplayerGameSubsystem>();
}

void UMultiplayerGameSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	const IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	OnlineSessionPtr = OnlineSubsystem->GetSessionInterface();
}

void UMultiplayerGameSubsystem::SetLocalSessionName_Internal(const FText& InNewSessionName)
{
	if (!InNewSessionName.EqualTo(LocalSessionName))
	{
		LocalSessionName = InNewSessionName;
		OnLocalSessionNameChanged.Broadcast(LocalSessionName);
	}
}

void UMultiplayerGameSubsystem::SetLocalSessionName(const FText& InNewSessionName, const UObject* WorldContextObject)
{
	GetSubsystem(WorldContextObject)->SetLocalSessionName_Internal(InNewSessionName);
}

FText UMultiplayerGameSubsystem::GetLocalSessionName(const UObject* WorldContextObject)
{
	return GetSubsystem(WorldContextObject)->LocalSessionName;
}

FString UMultiplayerGameSubsystem::CreateServerTravelLink(const FString& InWorldPath)
{
	FString ReturnBuffer = InWorldPath;
	int32 DotIndex = INDEX_NONE;
	if (ReturnBuffer.FindLastChar('.', DotIndex))
	{
		ReturnBuffer = ReturnBuffer.Left(DotIndex);
	}
	ReturnBuffer += TEXT("?listen");
	return ReturnBuffer;
}

void UMultiplayerGameSubsystem::CreateSession_Internal(const TMap<FName, FString>& InSessionSettings)
{
	
	CloseSession_Internal();

	TSharedPtr<FOnlineSessionSettings> SessionSettings = MakeShareable(new FOnlineSessionSettings());

	SessionSettings->bIsLANMatch = true;
	SessionSettings->NumPublicConnections = UMultiplayerGameConstants::GetMaxPublicConnections();
	SessionSettings->bShouldAdvertise = true;
	SessionSettings->bUsesPresence = true;
	SessionSettings->bAllowJoinInProgress = true;
	SessionSettings->bAllowJoinViaPresence = true;

	for (auto SessionSetting : InSessionSettings)
		SessionSettings->Set(SessionSetting.Key, SessionSetting.Value);

	OnlineSessionPtr->AddOnCreateSessionCompleteDelegate_Handle(
		FOnCreateSessionCompleteDelegate::CreateUObject(this, &UMultiplayerGameSubsystem::OnSessionCreated));

	OnlineSessionPtr->CreateSession(0, NAME_GameSession, *SessionSettings);
	
}

void UMultiplayerGameSubsystem::CloseSession_Internal()
{
	auto ExistingSession = OnlineSessionPtr->GetNamedSession(NAME_GameSession);
	if (ExistingSession != nullptr)
	{
		OnlineSessionPtr->DestroySession(NAME_GameSession);
		GetWorld()->ServerTravel(CreateServerTravelLink(
			UMultiplayerGameConstants::GetSessionDestroyedReturnWorldPath().ToString()));
	}
}

void UMultiplayerGameSubsystem::OnSessionCreated(FName InSessionName, bool InWasSuccessful)
{
	GetWorld()->ServerTravel(CreateServerTravelLink(
		UMultiplayerGameConstants::GetLobbyWorldPath().ToString()));
}

void UMultiplayerGameSubsystem::CreateSession(const TMap<FName, FString>& InSessionSettings,
                                              const UObject* WorldContextObject)
{
	GetSubsystem(WorldContextObject)->CreateSession_Internal(InSessionSettings);
}

void UMultiplayerGameSubsystem::CloseSession(const UObject* WorldContextObject)
{
	GetSubsystem(WorldContextObject)->CloseSession_Internal();
}
