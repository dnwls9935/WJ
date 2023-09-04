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
	, attack_range(100.0f)
	, attack_radius(50.0f)
	, left_leg_health(15.0f)
	, left_leg_destroy(false)
	, right_leg_health(15.0f)
	, right_leg_destroy(false)

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

	FHitResult hit_result;
	FCollisionQueryParams params(NAME_None, false, this);
	const auto result = GetWorld()->SweepSingleByChannel(hit_result
														, GetActorLocation()
														, GetActorLocation() + GetActorForwardVector() * attack_range
														, FQuat::Identity
														, ECollisionChannel::ECC_Pawn
														, FCollisionShape::MakeSphere(attack_radius)
														, params);

	auto trace_vector = GetActorForwardVector() * attack_range;
	auto center = GetActorLocation() + trace_vector * 0.5f;
	auto half_height = attack_range * 0.5f + attack_radius;
	auto capsule_rot = FRotationMatrix::MakeFromZ(trace_vector).ToQuat();
	auto draw_color = result ? FColor::Green : FColor::Red;
	auto debug_life_time = 5.0f;

	DrawDebugCapsule(GetWorld()
					, center
					, half_height
					, attack_radius
					, capsule_rot
					, draw_color
					, false
					, debug_life_time);

	if (result == true)
	{
		if (::IsValid(hit_result.GetActor()) == true)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, TEXT("Attack true"));
		}
	}


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

