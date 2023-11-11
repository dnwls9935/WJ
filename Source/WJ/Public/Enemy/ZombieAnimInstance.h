// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter/BaseAnimInstance.h"
#include "ZombieAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class WJ_API UZombieAnimInstance : public UBaseAnimInstance
{
	GENERATED_BODY()
	
public:
	UZombieAnimInstance();

public:
	virtual void PlayAttackMontage() noexcept;

private:
	UFUNCTION()
	void AnimNotify_AnimEnd();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	class UAnimMontage* attack_montage;
};
