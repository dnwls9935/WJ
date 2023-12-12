// Fill out your copyright notice in the Description page of Project Settings.


#include "Equip/Gun/Pistol.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
APistol::APistol()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	info.base_damage = 50.0f;
	info.status = WEAPON_STATUS::ONE_HAND_PISTOL;
}

// Called when the game starts or when spawned
void APistol::BeginPlay()
{
	max_ammo = 12;
	Super::BeginPlay();
	
	current_magazine = 24;
}

// Called every frame
void APistol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

