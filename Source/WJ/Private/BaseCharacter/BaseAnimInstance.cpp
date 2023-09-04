// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter/BaseAnimInstance.h"
#include "BaseCharacter/BaseCharacter.h"

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

	auto result = Cast<ABaseCharacter>(TryGetPawnOwner())->GetLegsBreak();
	if (result == false)
	{
		auto rand = FMath::RandRange(0, 2);
		auto section_name = FName("");

		switch (rand)
		{
		case 0:
			section_name = FName("LH_Stand");
			break;
		case 1:
			section_name = FName("RH_Stand");
			break;
		case 2:
			section_name = FName("BH_Stand");
			break;
		default:
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Attack Montage Rand Error"));
			return;
		}

		Montage_JumpToSection(section_name, attack_montage);
	}
	else
	{
		auto rand = FMath::RandRange(0, 1);
		auto section_name = FName("");

		switch (rand)
		{
		case 0:
			section_name = FName("LH_Crawl");
			break;
		case 1:
			section_name = FName("BH_Crawl");
			break;
		default:
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Attack Montage Rand Error"));
			return;
		}

		Montage_JumpToSection(section_name, attack_montage);
	}
}