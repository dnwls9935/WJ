// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter/BaseCharacter.h"
#include "InputActionValue.h"
#include "../Function/WJDefines.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class WJ_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	APlayerCharacter();

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable)
	inline bool IsEquipedWeapon() { return equip_weapon == nullptr ? false : true; }

	UFUNCTION(BlueprintCallable)
	inline class AGun* GetEquipedWeapon() { return IsEquipedWeapon() == true ? equip_weapon : nullptr; }

	UFUNCTION(BlueprintCallable)
	void SetEquipWeqpon(class AGun* _weapon) noexcept;

	UFUNCTION(BlueprintCallable)
	void ClearEquipWeapon() noexcept;

	UFUNCTION(BlueprintImplementableEvent, Category = "Reloading")
	void Reloading();

	UFUNCTION(BlueprintCallable)
	void CameraShaking() noexcept;

	UFUNCTION(BlueprintCallable)
	void EquipStateIsNone() noexcept;

	UFUNCTION(BlueprintCallable)
	void Move(float _speed) noexcept;

	void Tick(float _delta_time) override;

	FORCEINLINE const class AActor* GetFocusActor() const noexcept { return focus_actor; }

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void Attack() noexcept override;

private:
	void Look(const FInputActionValue& Value);
	void Equip(const FInputActionValue& Value);
	void Flash(const FInputActionValue& Value);
	void Interact(const FInputActionValue& Value);

	void Die() noexcept override;
	void Hit(const float _damage_amount) noexcept override;

	void Reload(const FInputActionValue& Value);

private:
	void SelectSlotInputEvnet(const FInputActionValue& _value) noexcept;
	void InventoryInputEvent(const FInputActionValue& _value) noexcept;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", Meta = (AllowPrivateAccess = true))
	class USpringArmComponent* spring_arm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", Meta = (AllowPrivateAccess = true))
	class UCameraComponent* camera;

	UPROPERTY(EditAnywhere, Category = "Input", Meta = (AllowPrivateAccess = true))
	class UInputMappingContext* player_input_mapping_context;

	UPROPERTY(EditAnywhere, Category = "Input", Meta = (AllowPrivateAccess = true))
	class UInputAction* select_slot_action;

	UPROPERTY(EditAnywhere, Category = "Input", Meta = (AllowPrivateAccess = true))
	class UInputAction* inventory_action;

	UPROPERTY(EditAnywhere, Category = "Input", Meta = (AllowPrivateAccess = true))
	class UInputAction* reload_action;

	UPROPERTY(EditAnywhere, Category = "Input", Meta = (AllowPrivateAccess = true))
	class UInputAction* flash_action;

	UPROPERTY(EditAnywhere, Category = "Input", Meta = (AllowPrivateAccess = true))
	class UInputAction* interact_action;

	UPROPERTY(EditDefaultsOnly, Category = "Montage", Meta = (AllowPrivateAccess = true))
	class UAnimMontage* attack_montage;

	UPROPERTY(EditDefaultsOnly, Category = "Montage", Meta = (AllowPrivateAccess = true))
	class UAnimMontage* one_hand_pistol_reload_montage;

	UPROPERTY(EditDefaultsOnly, Category = "Montage", Meta = (AllowPrivateAccess = true))
	class UAnimMontage* rifle_reload_montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage", Meta = (AllowPrivateAccess = true))
	class UAnimMontage* current_weapon_type_reload_montage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Player Status", Meta=(AllowPrivateAccess="true"))
	PLAYER_STATUS status;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Equip Info", meta=(AllowPrivateAccess="true"))
	class AGun* equip_weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slots", meta = (AllowPrivateAccess = "true"))
	class USlotComponent* slots_component;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCameraShakeBase> shake_classes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	bool				is_zoomm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Status", Meta = (AllowPrivateAccess = "true"))
	float current_movement_delta;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Status", Meta = (AllowPrivateAccess = "true"))
	float cross_hair_spread_multiplier;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Status", Meta = (AllowPrivateAccess = "true"))
	float corss_hair_velocity_factor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class AActor* camera_actor;

	class AWJGameMode* cast_game_mode;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input", Meta = (AllowPrivateAccess = "true"))
	float interact_distance;


	class AActor* focus_actor;

};
