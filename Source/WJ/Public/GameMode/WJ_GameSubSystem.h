// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "../Function/WJDefines.h"
#include "../Equip/Gun/Gun.h"
#include "WJ_GameSubSystem.generated.h"

/**
 * 
 */
UCLASS()
class WJ_API UWJ_GameSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:	
	void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION()
	FWeaponInfo GetWeaponInfo(const WEAPON_TYPE _key) noexcept;

	WEAPON_STATUS GetWeaponStatus(const WEAPON_TYPE _key) noexcept;

	UFUNCTION()
	WEAPON_STATUS GetWeaponStatus(const int _key) noexcept;
	
public:
	void Log() noexcept;
	


private:
	TMap<WEAPON_TYPE, FWeaponInfo> weapon_map;
};
