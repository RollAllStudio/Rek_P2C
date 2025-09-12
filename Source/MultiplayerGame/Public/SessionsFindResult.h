// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSessionSettings.h"
#include "UObject/Object.h"
#include "SessionsFindResult.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERGAME_API USessionsFindResult : public UObject
{
	GENERATED_BODY()

	TSharedPtr<FOnlineSessionSearch> SearchPtr;

public:

	void SetSearchPtr(TSharedPtr<FOnlineSessionSearch> InSearchPtr);
	TSharedPtr<FOnlineSessionSearch> GetSearchPtr() const
	{
		return SearchPtr;
	}
	
};
