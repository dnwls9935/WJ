// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Zombie.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimInstance.h"
#include "BaseCharacter/BaseAnimInstance.h"

AZombie::AZombie()
{
	max_health = 100;
}

void AZombie::BeginPlay()
{
	Super::BeginPlay();

	//bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void AZombie::PossessedBy(AController* _new_controller)
{
	Super::PossessedBy(_new_controller);
}

void AZombie::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	Super::OnAttackMontageEnded(Montage, bInterrupted);
}

void AZombie::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}
