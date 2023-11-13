// Fill out your copyright notice in the Description page of Project Settings.


#include "Equip/Gun/Gun.h"
#include "Components/PointLightComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SpotLightComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/WJGameMode.h"

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
	, current_magazine(0)
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

	flash = CreateDefaultSubobject<USpotLightComponent>(TEXT("Flash"));
	flash->SetupAttachment(muzzle_point);
	flash->SetVisibility(false);

}

void AGun::SetAttach(const bool _b) noexcept
{
	is_attached = _b;
	if (is_attached == true)
	{
		SetActorHiddenInGame(true);
		UpdateWeaponInfoToHUD();
	}
	else
	{
		SetActorHiddenInGame(false);
		UpdateWeaponInfoToHUD();
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
	
	UpdateWeaponInfoToHUD();

	return true;
}

void AGun::UpdateWeaponInfoToHUD()
{
	cast_game_mode->UpdateCurrentWidgetInfo(this);
}

void AGun::SetFlash() noexcept
{
	const bool b = flash->GetVisibleFlag();
	flash->SetVisibility(!b);
}

void AGun::BeginReload() noexcept
{
	is_reloading = true;
}

void AGun::EndReload() noexcept
{
	is_reloading = false;

	int minus = current_magazine - (max_ammo - current_ammo);
	if (minus > 0)
	{
		current_ammo = max_ammo;
		current_magazine = minus;
	}
	else
	{
		current_ammo += current_magazine;
		current_magazine = 0;
	}


	UpdateWeaponInfoToHUD();
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

	auto game_mode = UGameplayStatics::GetGameMode(GetWorld());
	if (game_mode != nullptr)
		cast_game_mode = Cast<AWJGameMode>(game_mode);

	UpdateWeaponInfoToHUD();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

