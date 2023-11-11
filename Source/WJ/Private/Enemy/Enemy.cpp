// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Enemy.h"
#include "BaseCharacter/BaseCharacter.h"
#include "BaseCharacter/BaseAnimInstance.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"	
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerCharacter.h"
#include "Equip/Gun/Gun.h"


AEnemy::AEnemy()
	: attack_range(100.0f)
	, is_attack(false)
	, attack_radius(50.0f)
	, left_leg_health(15.0f)
	, left_leg_destroy(false)
	, right_leg_health(15.0f)
	, right_leg_destroy(false)
	, target(nullptr)
	, attack_damage(15.0f)
	, enemy_spawn_type(ENEMY_SPAWN_TYPE::NORMAL)
	, intro_montage_index(0)
	, is_intro(false)
{
	actor_type = ACTOR_TYPE::ENEMY;
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemy::Attack() noexcept
{
	Super::Attack();
	hits.Empty();

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
		auto actor = Cast<APlayerCharacter>(hit_result.GetActor());
		if (::IsValid(actor) == true && hits.Find(actor) < 0)
		{
			hits.AddUnique(actor);
			UGameplayStatics::ApplyDamage(actor, attack_damage, GetController(), nullptr, NULL);
		}
	}

}

void AEnemy::SetGravity(const bool _b) noexcept
{
	GetMesh()->SetEnableGravity(_b);
}

void AEnemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	const float damaged_value = current_health - damage;

	if (DamageEvent.IsOfType(FPointDamageEvent::ClassID))
	{
		const FPointDamageEvent* point_damage_event = static_cast<const FPointDamageEvent*>(&DamageEvent);

		if (damaged_value <= 0)
			Die();
		else
		{
			Hit(damage, point_damage_event->HitInfo.Component->GetName());
			auto owner = Cast<AGun>(DamageCauser)->GetOwnerPlayer();

			SetTarget(owner);
			if(GetIsIntro() == true)
			{
				if (GetMesh()->GetAnimInstance()->Montage_IsPlaying(intro_montage) == false)
					BeginIntroMontage();
			}
		}
	}

	return damage;
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	BeginPlay(enemy_spawn_type);
}

void AEnemy::Hit(const float _damage_amout) noexcept
{
	Super::Hit(_damage_amout);
}

void AEnemy::Hit(const float _damage, const FString _name) noexcept
{
	Hit(current_health - ShootTarget(_damage, _name));
}

void AEnemy::Die() noexcept
{
	Super::Die();

	GetWorldTimerManager().SetTimer(dead_timer, this, &AEnemy::Destroy, 3.0);
}

const float AEnemy::ShootTarget(const float _damage, const FString _name) noexcept
{
	if (_name == "head")
		return _damage * 2;
	else if (_name == "spine_0")
		return _damage;
	else if (_name == "calf_l" || _name == "foot_l")
	{
		left_leg_health -= _damage;

		if (left_leg_health <= 0 && left_leg_destroy == false)
		{
			left_leg_destroy = true;
			left_leg_health = 0;
			GetCharacterMovement()->MaxWalkSpeed = movement_speed * 0.5f;
			movement_speed = GetCharacterMovement()->MaxWalkSpeed;
		}

		left_leg_health = FMath::Max<float>(left_leg_health, 0);
	}
	else if (_name == "calf_r" || _name == "foot_r")
	{
		right_leg_health -= _damage;

		if (right_leg_health <= 0 && right_leg_destroy == false)
		{
			right_leg_destroy = true;
			right_leg_health = 0;
			GetCharacterMovement()->MaxWalkSpeed = movement_speed * 0.5f;
			movement_speed = GetCharacterMovement()->MaxWalkSpeed;
		}

		right_leg_health = FMath::Max<float>(right_leg_health, 0);
	}
	else
		return _damage;

	return _damage;
}

void AEnemy::Destroy()
{
	Super::Destroy();
}

void AEnemy::BeginIntroMontage() noexcept
{
	FString slot_name;
	GetMesh()->GetAnimInstance()->Montage_Play(intro_montage);
	GetMesh()->GetAnimInstance()->Montage_JumpToSection(FName(*FString::Printf(TEXT("stand_up_%d"), intro_montage_index)), intro_montage);
}

void AEnemy::BeginPlay(ENEMY_SPAWN_TYPE _type) noexcept
{
	switch (_type)
	{
	case ENEMY_SPAWN_TYPE::NORMAL:
	{
		FString slot_name;
		GetMesh()->GetAnimInstance()->Montage_Play(intro_montage);
		GetMesh()->GetAnimInstance()->Montage_JumpToSection(FName(*FString::Printf(TEXT("stand_up_%d"), intro_montage_index)), intro_montage);
		GetMesh()->GetAnimInstance()->Montage_Pause();
		is_intro = true;
		break;
	}
	case ENEMY_SPAWN_TYPE::INTERACT:
		GetMesh()->GetAnimInstance()->Montage_Play(intro_montage);
		is_intro = false;
		break;
	case ENEMY_SPAWN_TYPE::NONE:
		break;
	default:
		break;
	}
}
