// Fill out your copyright notice in the Description page of Project Settings.


#include "Equip/Gun/Gun.h"
#include "Components/PointLightComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGun::AGun()
	: mesh(nullptr)
	, is_attached(false)
	, can_fire(true)
	, fire_rate(0.1f)
	, is_reloading(false)
	, max_ammo(0)
	, current_ammo(0)
	, owner_player_actor(nullptr)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	SetRootComponent(mesh);

	muzzle_point = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle Point"));
	muzzle_point->SetupAttachment(GetRootComponent());

	fire_light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Fire Light"));
	fire_light->SetupAttachment(muzzle_point);

	fire_light->SetLightFColor(FColor(225, 171, 53, 255));
	fire_light->SetVisibility(false);

	muzzle_effect = CreateDefaultSubobject<UParticleSystem>(TEXT("Muzzle Effect"));

}

void AGun::SetAttach(const bool _b) noexcept
{
	is_attached = _b;
	if (is_attached == true)
	{
		SetActorHiddenInGame(true);
	}
	else
	{
		SetActorHiddenInGame(false);
	}
}

bool AGun::Fire() noexcept
{
	GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Blue, *FString::Printf(TEXT("%d / %d"), current_ammo, max_ammo));
	if (can_fire == false || current_ammo <= 0)
		return false;

	current_ammo--;
	can_fire = false;
	fire_light->SetVisibility(true);
	GetWorldTimerManager().SetTimer(fire_light_timer, this, &AGun::TurnOffMuzzleEffect, 0.05f);
	GetWorldTimerManager().SetTimer(fire_timer, this, &AGun::CanFire, fire_rate);
	
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), muzzle_effect, muzzle_point->GetComponentTransform());

	return true;
}

void AGun::BeginReload() noexcept
{
	is_reloading = true;
}

void AGun::EndReload() noexcept
{
	is_reloading = false;


	current_ammo = max_ammo;
	/*int current = current_magazine - current_ammo;
	if (current < 0)
	{
		current_ammo = current_ammo + current;
	}
	else
	{
	}*/
}

void AGun::CanFire() noexcept
{
	can_fire = true;
}

void AGun::TurnOffMuzzleEffect() noexcept
{
	fire_light->SetVisibility(false);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
	current_ammo = max_ammo;
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

