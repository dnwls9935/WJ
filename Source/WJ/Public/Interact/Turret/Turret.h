// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interact/InteractActor.h"
#include "../../Function/WJDefines.h"
#include "Turret.generated.h"

/**
 * 
 */
UCLASS()
class WJ_API ATurret : public AInteractActor
{
	GENERATED_BODY()
	
public:
	ATurret();
	
public:
	void BeginPlay() override;
	void Tick(float _deltaTime) override;
	const bool Interact(AActor* _interacting_actor) noexcept override;
	const bool AttachActor(const bool _b, class APlayerCharacter* _player) noexcept;

private:
	void Idle(float _deltaTime) noexcept;
	void Attack(float _deltaTime) noexcept;
	void CheckRadius(float _deltaTime) noexcept;
	void IdelStopRotation() noexcept;

	void CheckAttackRange(float _deltaTime) noexcept;


	void Fire(float _deltaTime) noexcept;
	void Reload(float _deltaTime) noexcept;


private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* base;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* body;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* barrel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	class USceneComponent*		muzzle_position;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Info", meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* muzzle_effect;


	class ABaseCharacter* current_target;

	bool idle_dir;
	FTimerHandle idle_rot_timer;
	TURRET_STATE state;


	bool can_fire;
	FTimerHandle fire_timer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float fire_rate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float base_damage;

	bool is_attach;
};
