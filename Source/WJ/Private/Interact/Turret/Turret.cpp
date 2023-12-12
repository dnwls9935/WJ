// Fill out your copyright notice in the Description page of Project Settings.


#include "Interact/Turret/Turret.h"
#include "BaseCharacter/BaseCharacter.h"
#include "Enemy/Enemy.h"
#include "Player/PlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystemComponent.h"

ATurret::ATurret()
	: base(nullptr)
	, body(nullptr)
	, barrel(nullptr)
	, current_target(nullptr)
	, idle_dir(false)
	, state(TURRET_STATE::NONE)
	, can_fire(true)
	, fire_rate(0.2f)
	, base_damage(50.0f)
	, is_attach(false)
{
	base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("base mesh"));
	SetRootComponent(base);

	body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("body mesh"));
	body->SetupAttachment(base);

	barrel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("barrel mesh"));
	barrel->SetupAttachment(body);

	muzzle_position = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("muzzle position"));
	muzzle_position->SetupAttachment(barrel);

	muzzle_effect = CreateDefaultSubobject<UParticleSystem>(TEXT("Muzzle Effect"));

	state = TURRET_STATE::IDEL_ROT;

	interact_type = INTERACT_TYPE::TURRET;
}

void ATurret::BeginPlay()
{
	Super::BeginPlay();
	is_attach = true;
}

void ATurret::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);

	if (is_attach == true)
		return;

	CheckAttackRange(_deltaTime);

	if (current_target != nullptr)
	{
		if (current_target->GetDead() == true || current_target->GetHeath() <= 0)
		{
			state = TURRET_STATE::IDEL_ROT;
			current_target = nullptr;
		}
	}
	
	if (current_target == nullptr || current_target->GetDead() == true || current_target->GetHeath() <= 0)
		Idle(_deltaTime);
	else
		Attack(_deltaTime);
	
}

const bool ATurret::Interact(AActor* _interacting_actor) noexcept
{
	auto result = Super::Interact(_interacting_actor);
	if (result == false)
		return result;



	return true;
}

void ATurret::Idle(float _deltaTime) noexcept
{
	switch (state)
	{
	case TURRET_STATE::IDEL_ROT:
	{
		auto rot = body->GetRelativeRotation();
		auto yaw = rot.Yaw;

		if (idle_dir == false)
		{
			yaw -= _deltaTime * 50.0f;
			if (yaw <= -30)
			{
				idle_dir = !idle_dir;
				CheckRadius(_deltaTime);
			}
		}
		else
		{
			yaw += _deltaTime * 50.0f;
			if (yaw >= +30)
			{
				idle_dir = !idle_dir;
				CheckRadius(_deltaTime);
			}
		}
		rot.Yaw = yaw;
		body->SetRelativeRotation(rot);
	}
		break;
	case TURRET_STATE::IDLE_ROT_STOP:
	{
		auto time = GetWorldTimerManager().GetTimerElapsed(idle_rot_timer);
		if (time <= -1)
			IdelStopRotation();
	}
		break;
	}
}

void ATurret::Attack(float _deltaTime) noexcept
{
	if (current_target == nullptr)
		return;

	auto rot = body->GetRelativeRotation();

	auto vec = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), current_target->GetActorLocation());
	rot.Yaw = vec.Yaw + (-80.0f);

	body->SetRelativeRotation(rot);
	
	if (can_fire == true)
		Fire(_deltaTime);
	else
		Reload(_deltaTime);
}

void ATurret::CheckRadius(float _deltaTime) noexcept
{
	GetWorldTimerManager().SetTimer(idle_rot_timer, 1.5f, false);
	state = TURRET_STATE::IDLE_ROT_STOP;
}

void ATurret::IdelStopRotation() noexcept
{
	state = TURRET_STATE::IDEL_ROT;
	GetWorldTimerManager().ClearTimer(idle_rot_timer);
}

void ATurret::CheckAttackRange(float _deltaTime) noexcept
{
	current_target = nullptr;

	TArray<FOverlapResult> overlap_results;
	FCollisionQueryParams collision_query_params(NAME_None, false, this);
	auto result = GetWorld()->OverlapMultiByChannel(overlap_results
		, GetActorLocation()
		, FQuat::Identity
		, ECollisionChannel::ECC_Pawn
		, FCollisionShape::MakeSphere(2000.0f)
		, collision_query_params);

	if (result == true && current_target == nullptr)
	{
		for (auto pawn : overlap_results)
		{
			if (pawn.GetActor() == nullptr)
				continue;

			if (pawn.GetActor()->ActorHasTag(FName("Enemy")) == false)
				continue;

			auto cast_pawn = Cast<AEnemy>(pawn.GetActor());
			if (cast_pawn == nullptr)
				continue;

			if (cast_pawn->GetDead() == true || cast_pawn->GetHeath() <= 0)
				continue;

			current_target = cast_pawn;
		}
	}

	if (current_target != nullptr)
		state = TURRET_STATE::ATTACK;
	else
		state = TURRET_STATE::IDEL_ROT;
}

void ATurret::Fire(float _deltaTime) noexcept
{
	if (can_fire == false)
		return;

	can_fire = false;
	
	
	auto start = muzzle_position->GetComponentLocation();
	auto end = current_target->GetActorLocation();

	FHitResult hit_result;
	FCollisionQueryParams params;
	TArray<AActor*> ignores;
	ignores.Add(interacting_actor);
	ignores.Add(this);

	params.AddIgnoredActors(ignores);

	auto result = GetWorld()->LineTraceSingleByChannel(hit_result, start, end, ECollisionChannel::ECC_Pawn, params);

	if (result == true)
	{
		GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Yellow, FString::Printf(TEXT("%s"), *hit_result.GetActor()->GetName()));
		
		FHitResult out_hit;
		out_hit.Component = hit_result.GetComponent();
		out_hit.ImpactPoint = hit_result.ImpactPoint;
		out_hit.ImpactNormal = hit_result.ImpactNormal;
		UGameplayStatics::ApplyPointDamage(hit_result.GetActor(), base_damage, hit_result.GetActor()->GetActorLocation(), out_hit, this->GetInstigatorController(), this, nullptr);
	}

	GetWorldTimerManager().SetTimer(fire_timer, fire_rate, false);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), muzzle_effect, muzzle_position->GetComponentTransform());
}

void ATurret::Reload(float _deltaTime) noexcept
{
	if (can_fire == true)
		return;

	auto time = GetWorldTimerManager().GetTimerElapsed(fire_timer);
	if (time >= fire_rate || time < 0)
		can_fire = true;
}

const bool ATurret::AttachActor(const bool _b, APlayerCharacter* _player) noexcept
{
	if (_b == false)
	{
		is_attach = false;

		GetRootComponent()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		SetActorRotation(FRotator::ZeroRotator);


		FHitResult hit_result;
		FCollisionQueryParams params;

		auto down = GetActorUpVector().GetSafeNormal() * -1.0f;
		auto result = GetWorld()->LineTraceSingleByChannel(hit_result, GetTransform().GetLocation(), GetActorLocation() + (down * 1000.0f), ECollisionChannel::ECC_WorldStatic, params);
		if (result == true)
		{
			auto actor = hit_result.GetActor();
			SetActorLocation(hit_result.ImpactPoint);
		}

		return is_attach;
	}
	

	is_attach = _b;
	AttachToComponent(_player->GetInteractPoint(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	return is_attach;
}
