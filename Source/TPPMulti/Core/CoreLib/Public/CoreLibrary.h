// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CoreLibrary.generated.h"

/**
 * 
 */
UCLASS()
class TPPMULTI_API UCoreLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

#pragma region UI_TEXT_HELPERS
	
public:

	UFUNCTION(BlueprintCallable, Category = "UI|TextHelpers")
	static bool IsTextValid(const FText& InText, const int InMaxTextLen);

#pragma endregion 
	
};
