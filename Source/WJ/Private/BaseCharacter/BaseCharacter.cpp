// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter/BaseCharacter.h"
#include "Animation/AnimInstance.h"
#include "BaseCharacter/BaseAnimInstance.h"
#include "Enemy/AI/Controller/Base_AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
	: max_health(-1)
	, current_health(-1)
	, animinstance(nullptr)
	, is_dead(false)
	, movement_speed(0)
	, actor_type(ACTOR_TYPE::NONE)

{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	current_health = max_health;
	movement_speed = GetCharacterMovement()->MaxWalkSpeed;
}

void ABaseCharacter::Die() noexcept
{
	if (is_dead == true)
		return;

	is_dead = true;

	current_health = 0;

	Ragdoll();
}

void ABaseCharacter::Hit(const float _damage_amount) noexcept
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("%s"), *this->GetName()));

	current_health = _damage_amount;
}

void ABaseCharacter::Ragdoll() noexcept
{
	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
	GetMesh()->SetSimulatePhysics(true);

	auto impulse_direction = GetActorRotation().Vector() * -1.0f;
	impulse_direction.Normalize();

	auto impulse_strength = 1500.0f;

	auto final_impulse = impulse_direction * impulse_strength;
	GetMesh()->SetPhysicsLinearVelocity(FVector::ZeroVector);
	GetMesh()->AddImpulseToAllBodiesBelow(final_impulse, NAME_None);

	if (GetCapsuleComponent() != nullptr)
		GetCapsuleComponent()->DestroyComponent();

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
	
}

void ABaseCharacter::OnAttackMontageEnded(UAnimMontage* _montage, bool _interrupted)
{
}

void ABaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	animinstance = Cast<UBaseAnimInstance>(GetMesh()->GetAnimInstance());

	if (animinstance != nullptr)
		animinstance->OnMontageEnded.AddDynamic(this, &ABaseCharacter::OnAttackMontageEnded);
}
