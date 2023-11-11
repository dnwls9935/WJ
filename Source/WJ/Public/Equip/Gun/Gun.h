// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../Function/WJDefines.h"
#include "Gun.generated.h"

USTRUCT(BlueprintType)
struct FWeaponInfo
{
	GENERATED_BODY()
public:
	FWeaponInfo() : base_damage(0), status(WEAPON_STATUS::NONE) {}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info", meta = (AllowPrivateAccess = "true"))
	float base_damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info", meta = (AllowPrivateAccess = "true"))
	WEAPON_STATUS	status;
};

UCLASS()
class WJ_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

public:

	UFUNCTION(BlueprintCallable)
	void SetAttach(const bool _b) noexcept;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool GetAttach() noexcept { return is_attached;}

	UFUNCTION(BlueprintCallable)
	bool Fire() noexcept;

	UFUNCTION(BlueprintCallable)
	void SetReload(bool _b) noexcept { is_reloading = _b; };

	UFUNCTION(BlueprintCallable)
	bool GetReload() noexcept { return is_reloading; };

	UFUNCTION(BlueprintCallable)
	void BeginReload() noexcept;

	UFUNCTION(BlueprintCallable)
	void EndReload() noexcept;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE int GetCurrentAmmo() {return current_ammo;}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE int GetMaxAmmo() { return max_ammo; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE int GetCurrentMagazine() { return current_magazine; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE int GetMaxMagazine() { return max_magazine; }

	FORCEINLINE bool CanReload() noexcept { return (GetReload() == false) && (current_ammo < max_ammo); }

	FORCEINLINE class APlayerCharacter* GetOwnerPlayer() const noexcept { return owner_player_actor; }
	FORCEINLINE void SetOwnerPlayer(class APlayerCharacter* _player) noexcept { owner_player_actor = _player; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void CanFire() noexcept;
	void TurnOffMuzzleEffect() noexcept;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	WEAPON_STATUS GetWeaponType() { return info.status; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attach Status", meta = (AllowPrivateAccess="true"))
	bool is_attached;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess="true"))
	class USkeletalMeshComponent*		mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Info", meta = (AllowPrivateAccess = "true"))
	FWeaponInfo	info;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Info", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* muzzle_point;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Info", meta = (AllowPrivateAccess = "true"))
	class UPointLightComponent* fire_light;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Info", meta = (AllowPrivateAccess = "true"))
	bool				can_fire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Info", meta = (AllowPrivateAccess = "true"))
	float				fire_rate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Info", meta = (AllowPrivateAccess = "true"))
	int					current_ammo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Info", meta = (AllowPrivateAccess = "true"))
	int					max_ammo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Info", meta = (AllowPrivateAccess = "true"))
	int					current_magazine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Info", meta = (AllowPrivateAccess = "true"))
	int					max_magazine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Info", meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* muzzle_effect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class APlayerCharacter* owner_player_actor;


	FTimerHandle		fire_timer;
	FTimerHandle		fire_light_timer;

	bool				is_reloading;

	
};
