// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerGameSubsystem.h"
#include "MultiplayerGameConstants.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "SessionsFindResult.h"
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
	OnlineSessionsPtr = OnlineSubsystem->GetSessionInterface();

	OnlineSessionsPtr->AddOnCreateSessionCompleteDelegate_Handle(
		FOnCreateSessionCompleteDelegate::CreateUObject(this, &UMultiplayerGameSubsystem::OnSessionCreated));

	OnlineSessionsPtr->AddOnFindSessionsCompleteDelegate_Handle(
		FOnFindSessionsCompleteDelegate::CreateUObject(this, &UMultiplayerGameSubsystem::OnSessionSearchComplete));

	OnlineSessionsPtr->AddOnJoinSessionCompleteDelegate_Handle(
		FOnJoinSessionCompleteDelegate::CreateUObject(this, &UMultiplayerGameSubsystem::OnJoinSessionComplete));
}

void UMultiplayerGameSubsystem::SetLocalSessionName_Internal(const FText& InNewSessionName)
{
	if (!InNewSessionName.EqualTo(LocalHostedSessionName))
	{
		LocalHostedSessionName = InNewSessionName;
		OnLocalSessionNameChanged.Broadcast(LocalHostedSessionName);
	}
}

void UMultiplayerGameSubsystem::SetLocalHostedSessionName(const FText& InNewSessionName, const UObject* WorldContextObject)
{
	GetSubsystem(WorldContextObject)->SetLocalSessionName_Internal(InNewSessionName);
}

FText UMultiplayerGameSubsystem::GetLocalHostedSessionName(const UObject* WorldContextObject)
{
	return GetSubsystem(WorldContextObject)->LocalHostedSessionName;
}

FText UMultiplayerGameSubsystem::GetLocalJoinedSessionName(const UObject* WorldContextObject)
{
	return GetSubsystem(WorldContextObject)->LocalJoinedSessionName;
}

bool UMultiplayerGameSubsystem::IsHost(const UObject* WorldContextObject)
{
	return GetSubsystem(WorldContextObject)->bIsHost;
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
	bIsHost = true;

	TSharedPtr<FOnlineSessionSettings> SessionSettings = MakeShareable(new FOnlineSessionSettings());

	SessionSettings->bIsLANMatch = true;
	SessionSettings->NumPublicConnections = UMultiplayerGameConstants::GetMaxPublicConnections();
	SessionSettings->bShouldAdvertise = true;
	SessionSettings->bUsesPresence = true;
	SessionSettings->bAllowJoinInProgress = true;
	SessionSettings->bAllowJoinViaPresence = true;

	for (auto SessionSetting : InSessionSettings)
		SessionSettings->Set(	SessionSetting.Key,
								SessionSetting.Value,
								EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

	LocalJoinedSessionName = LocalHostedSessionName;
	OnlineSessionsPtr->CreateSession(0, NAME_GameSession, *SessionSettings);
	
}

void UMultiplayerGameSubsystem::CloseSession_Internal()
{
	auto ExistingSession = OnlineSessionsPtr->GetNamedSession(NAME_GameSession);
	if (ExistingSession != nullptr)
	{
		FString TravelLink = CreateServerTravelLink(
			UMultiplayerGameConstants::GetSessionDestroyedReturnWorldPath().ToString());

		if (bIsHost)
		{
			GetWorld()->ServerTravel(TravelLink);
		}
		else
		{
			UGameplayStatics::GetGameInstance(this)->GetFirstLocalPlayerController()->ClientTravel(
				TravelLink, TRAVEL_Absolute);
		}

		OnlineSessionsPtr->DestroySession(NAME_GameSession);
		
	}
}

void UMultiplayerGameSubsystem::StartFindSessionsLoop_Internal()
{
	if (!bLoopingFindSessions)
		bLoopingFindSessions = true;

	if (!bIsLookingForSessions)
	{
		bIsLookingForSessions = true;
		StartNextFindSessions();
	}
}

void UMultiplayerGameSubsystem::StopFindSessionsLoop_Internal()
{
	if (bLoopingFindSessions)
		bLoopingFindSessions = false;
}

void UMultiplayerGameSubsystem::StartNextFindSessions()
{
	SessionSearchPtr = MakeShareable(new FOnlineSessionSearch());
	SessionSearchPtr->MaxSearchResults = UMultiplayerGameConstants::GetMaxSessionsFind();
	SessionSearchPtr->bIsLanQuery = true;
	OnlineSessionsPtr->FindSessions(0, SessionSearchPtr.ToSharedRef());
}

void UMultiplayerGameSubsystem::JoinSessionByIndex_Internal(const int32& InSessionIndex)
{
	bLoopingFindSessions = false;
	FOnlineSessionSearchResult SessionSearchResult = SessionSearchPtr.Get()->SearchResults[InSessionIndex];
	FString SessionNameSetting;
	SessionSearchResult.Session.SessionSettings.Get(
		SESSION_SETTING_NAME_SESSION_NAME, SessionNameSetting);
	LocalJoinedSessionName = FText::FromString(SessionNameSetting);

	bIsHost = false;
	OnStartJoiningSession.Broadcast();
	OnlineSessionsPtr->JoinSession(0, NAME_GameSession, SessionSearchResult);
}

void UMultiplayerGameSubsystem::OnSessionCreated(FName InSessionName, bool InWasSuccessful)
{
	GetWorld()->ServerTravel(CreateServerTravelLink(
		UMultiplayerGameConstants::GetLobbyWorldPath().ToString()));
}

void UMultiplayerGameSubsystem::OnSessionSearchComplete(bool InWasSuccessful)
{
	if (bLoopingFindSessions)
	{

		USessionsFindResult* ResultObj = NewObject<USessionsFindResult>(this);
		ResultObj->SetSearchPtr(SessionSearchPtr);
		OnSessionsFindComplete.Broadcast(ResultObj);
		
		StartNextFindSessions();
		return;
	}

	bIsLookingForSessions = false;
}

void UMultiplayerGameSubsystem::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{

	FString ConnectInfo;
	OnlineSessionsPtr->GetResolvedConnectString(SessionName, ConnectInfo);
	UGameplayStatics::GetGameInstance(this)->GetFirstLocalPlayerController()->ClientTravel(
		ConnectInfo, TRAVEL_Absolute);
	
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

void UMultiplayerGameSubsystem::StartFindSessionsLoop(const UObject* WorldContextObject)
{
	GetSubsystem(WorldContextObject)->StartFindSessionsLoop_Internal();
}

void UMultiplayerGameSubsystem::StopFindSessionsLoop(const UObject* WorldContextObject)
{
	GetSubsystem(WorldContextObject)->StopFindSessionsLoop_Internal();
}

void UMultiplayerGameSubsystem::JoinSessionByIndex(const UObject* WorldContextObject, const int32& InSessionIndex)
{
	GetSubsystem(WorldContextObject)->JoinSessionByIndex_Internal(InSessionIndex);
}
