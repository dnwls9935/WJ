// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter/BaseCharacter.h"
#include "Animation/AnimInstance.h"
#include "BaseCharacter/BaseAnimInstance.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
	: max_health(-1)
	, current_health(-1)
	, is_attack(false)
	, animinstance(nullptr)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	current_health = max_health;
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseCharacter::Attack() noexcept
{
	is_attack = true;
	animinstance->PlayAttackMontage();
}

void ABaseCharacter::OnAttackMontageEnded(UAnimMontage* _montage, bool _interrupted)
{
	on_attack_end.Broadcast();
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("BaseCharacter OnAttackMontageEnded"));
}

void ABaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	animinstance = Cast<UBaseAnimInstance>(GetMesh()->GetAnimInstance());

	if (animinstance != nullptr)
		animinstance->OnMontageEnded.AddDynamic(this, &ABaseCharacter::OnAttackMontageEnded);
}

