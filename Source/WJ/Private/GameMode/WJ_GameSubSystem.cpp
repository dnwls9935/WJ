// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/WJ_GameSubSystem.h"

void UWJ_GameSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	FWeaponInfo info;
	info.base_damage = 10;
	info.status = WEAPON_STATUS::ONE_HAND_PISTOL;
	
	weapon_map.Add(WEAPON_TYPE::PISTOL, info);


	info.base_damage = 15;
	info.status = WEAPON_STATUS::RIFLE;

	weapon_map.Add(WEAPON_TYPE::RIFLE, info);
}

FWeaponInfo UWJ_GameSubSystem::GetWeaponInfo(const WEAPON_TYPE _key) noexcept
{
	auto value = weapon_map.Find(_key);
	if(value == nullptr)
		return FWeaponInfo();

	return *value;
}

WEAPON_STATUS UWJ_GameSubSystem::GetWeaponStatus(const WEAPON_TYPE _key) noexcept
{
	auto value = GetWeaponInfo(_key);
	if (value.status == WEAPON_STATUS::NONE)
		return WEAPON_STATUS::NONE;

	return value.status;
}

WEAPON_STATUS UWJ_GameSubSystem::GetWeaponStatus(const int _key) noexcept
{
	return GetWeaponStatus(static_cast<WEAPON_TYPE>(_key));
}

void UWJ_GameSubSystem::Log() noexcept
{

}

