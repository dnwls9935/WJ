// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter/BaseCharacter.h"
#include "Zombie.generated.h"

/**
 * 
 */
UCLASS()
class WJ_API AZombie : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	AZombie();
	
public:
	void BeginPlay() override;
	void PossessedBy(AController* _new_controller) override;
	virtual void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted) override;
	void PostInitializeComponents() override;

private:

};
