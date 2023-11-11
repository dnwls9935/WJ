// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equip/Gun/Gun.h"
#include "Rifle.generated.h"

/**
 * 
 */
UCLASS()
class WJ_API ARifle : public AGun
{
	GENERATED_BODY()
	
public:
	ARifle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
};
