// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemDecription.generated.h"

/**
 * 
 */
UCLASS()
class WJ_API UItemDecription : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetFocus(const bool _result) noexcept;
};
