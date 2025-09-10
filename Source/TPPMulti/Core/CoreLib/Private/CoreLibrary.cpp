// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPMulti/Core/CoreLib/Public/CoreLibrary.h"

bool UCoreLibrary::IsTextValid(const FText& InText, const int InMaxTextLen)
{
	return InText.ToString().Len() <= InMaxTextLen;
}
