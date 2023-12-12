// Fill out your copyright notice in the Description page of Project Settings.


#include "Equip/Gun/Rifle.h"

ARifle::ARifle()
{
	info.base_damage = 65.0f;
	info.status = WEAPON_STATUS::RIFLE;
}

void ARifle::BeginPlay()
{
	max_ammo = 30;
	Super::BeginPlay();

	current_magazine = 60;
}
