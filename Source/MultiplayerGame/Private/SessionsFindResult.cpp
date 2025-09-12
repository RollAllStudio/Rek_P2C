// Fill out your copyright notice in the Description page of Project Settings.


#include "SessionsFindResult.h"

void USessionsFindResult::SetSearchPtr(TSharedPtr<FOnlineSessionSearch> InSearchPtr)
{
	SearchPtr = InSearchPtr;
}
