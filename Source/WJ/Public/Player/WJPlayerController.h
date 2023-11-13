// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WJPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class WJ_API AWJPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;
	
};
