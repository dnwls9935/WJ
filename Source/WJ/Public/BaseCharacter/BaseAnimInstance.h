// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class WJ_API UBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UBaseAnimInstance();

	void PlayAttackMontage() noexcept;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	class UAnimMontage* attack_montage;
};
