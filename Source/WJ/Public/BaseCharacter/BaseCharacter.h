// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Function/WJDefines.h"
#include "BaseCharacter.generated.h"

UCLASS()
class WJ_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Attack() noexcept;

	UFUNCTION()
	virtual void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	virtual void PostInitializeComponents() override;

	FORCEINLINE const bool GetDead() const noexcept { return is_dead; }
	FORCEINLINE const float GetHeath() const noexcept { return current_health; }

	FORCEINLINE const ACTOR_TYPE GetActorType() const noexcept { return actor_type; }


protected:
	virtual void BeginPlay() override;
	virtual void Die() noexcept;
	virtual void Hit(const float _damage_amount) noexcept;

private:
	void Ragdoll() noexcept;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Status", meta=(AllowPrivateAccess="true"))
	float max_health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status", meta = (AllowPrivateAccess = "true"))
	float current_health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status", meta = (AllowPrivateAccess = "true"))
	ACTOR_TYPE actor_type;

	UPROPERTY()
	class UBaseAnimInstance* animinstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Dead", Meta = (AllowPrivateAccess = "true"))
	bool is_dead;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement", Meta = (AllowPrivateAccess = "true"))
	float movement_speed;
};
