// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter/BaseCharacter.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"	

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(FOnAttackEnd_Delegate);

UCLASS()
class WJ_API AEnemy : public ABaseCharacter
{
	GENERATED_BODY()
public:
	AEnemy();

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void Attack() noexcept;

	void SetGravity(const bool _b) noexcept;


	FORCEINLINE const bool GetLegsBreak() const noexcept { return right_leg_destroy == true && left_leg_destroy == true; }
	FORCEINLINE class AActor* GetTarget() const noexcept { return target; }
	FORCEINLINE void SetTarget(class AActor* _target) noexcept { target = _target; }
	FORCEINLINE void SetIsAttack(const bool _bool) noexcept { is_attack = _bool; hits.Empty(); }
	FORCEINLINE const bool CanAttack() const noexcept { return is_attack; }
	FORCEINLINE void SetSpawnType(ENEMY_SPAWN_TYPE _type) { enemy_spawn_type = _type; }
	FORCEINLINE const bool GetIsIntro() const noexcept { return is_intro; }
	FORCEINLINE void SetIsIntro(const bool _intro) noexcept { is_intro = _intro; }


	UFUNCTION(BlueprintCallable)
	void EndIntro() noexcept {SetIsIntro(false); }

	void BeginPlay(ENEMY_SPAWN_TYPE _type) noexcept;
	void BeginIntroMontage() noexcept;

	void WakeUpEvent(float _time, class AActor* _target) noexcept;

protected:
	virtual void BeginPlay() override;
	void Hit(const float _damage_amout) noexcept override;
	void Hit(const float _damage, const FString _name) noexcept;
	void Die() noexcept;

private:
	const float ShootTarget(const float _damage, const FString _name) noexcept;

	void Destroy();

public:
	FOnAttackEnd_Delegate on_attack_end;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	bool	is_attack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = "true"))
	float attack_range;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = "true"))
	float attack_radius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Attack", Meta=(ALlowPrivateAccess = "true"))
	float attack_damage;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "left Leg", Meta = (AllowPrivateAccess = "true"))
	float left_leg_health;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "left Leg", Meta = (AllowPrivateAccess = "true"))
	bool left_leg_destroy;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Right Leg", Meta = (AllowPrivateAccess = "true"))
	float right_leg_health;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Right Leg", Meta = (AllowPrivateAccess = "true"))
	bool right_leg_destroy;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target", Meta = (AllowPrivateAccess = "true"))
	class AActor* target;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn Info", Meta = (AllowPrivateAccess = "true"))
	ENEMY_SPAWN_TYPE enemy_spawn_type;

	FTimerHandle dead_timer;

	TArray<AActor*>		hits;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit", meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* hit_effect;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage", Meta = (AllowPrivateAccess = true))
	class UAnimMontage* intro_montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage", Meta = (AllowPrivateAccess = true))
	int intro_montage_index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intro", Meta = (AllowPrivateAccess = true))
	bool is_intro;

};
