// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter/BaseAnimInstance.h"

UBaseAnimInstance::UBaseAnimInstance()
	: attack_montage(nullptr)
{
}

void UBaseAnimInstance::PlayAttackMontage() noexcept
{
	if (attack_montage == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Attack Montage is null"));
		return;
	}

	Montage_Play(attack_montage);
}