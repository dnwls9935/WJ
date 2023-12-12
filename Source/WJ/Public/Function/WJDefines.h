#pragma once

UENUM(BlueprintType)
enum class PLAYER_STATUS : uint8
{
	NONE_EQUIPED			UMETA(DisplayName = "None Equiped"),
	ONE_HAND_WEAPON			UMETA(DisplayName = "One Hand Weapon"),
	TWO_HAND_WEAPON			UMETA(DisplayName = "Two Hand Weapon"),
	THROW_HAND_WEAPON		UMETA(DisplayName = "Throw Hand Weapon"),
};


UENUM(BlueprintType)
enum class WEAPON_STATUS : uint8
{
	ONE_HAND_PISTOL			UMETA(DisplayName = "One Hand Pistol"),
	TWO_HAND_PISTOL			UMETA(DisplayName = "Two Hand Pistol"),
	RIFLE					UMETA(DisplayName = "Rifle"),
	NONE					UMETA(DisplayName = "None"),
};


UENUM(BlueprintType)
enum class WEAPON_TYPE : uint8
{
	PISTOL			UMETA(DisplayName = "Pistol"),
	RIFLE			UMETA(DisplayName = "Rifle"),
	NONE			UMETA(DisplayName = "None"),
};


UENUM(BlueprintType)
enum class ENEMY_SPAWN_TYPE : uint8
{
	NORMAL			UMETA(DisplayName = "Normal"),
	INTERACT		UMETA(DisplayName = "Interact"),
	DEFENSE			UMETA(DisplayName = "Defense"),
	NONE			UMETA(DisplayName = "None"),
};

UENUM(BlueprintType)
enum class ACTOR_TYPE : uint8
{
	PLAYER			UMETA(DisplayName = "Player"),
	ENEMY			UMETA(DisplayName = "Enemy"),
	INTERACT		UMETA(DisplayName = "Interact"),
	NONE			UMETA(DisplayName = "None"),
};

UENUM(BlueprintType)
enum class INTERACT_TYPE : uint8
{
	AMMO_BOX		UMETA(DisplayName = "Ammo Box"),
	EQUIP_WEAPON	UMETA(DisplayName = "Equip Weapon"),
	BUTTON			UMETA(DisplayName = "Button"),
	TURRET			UMETA(DisplayName = "TURRET"),
	NONE			UMETA(DisplayName = "None"),
};


UENUM(BlueprintType)
enum class TURRET_STATE : uint8
{
	IDEL_ROT		UMETA(DisplayName = "Idle Rot"),
	IDLE_ROT_STOP	UMETA(DisplayName = "Idle Rot Stop"),
	ATTACK			UMETA(DisplayName = "Attack"),
	NONE			UMETA(DisplayName = "None"),
};