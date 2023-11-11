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

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void Attack() noexcept override;

private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Equip(const FInputActionValue& Value);
	void PlayAttackMontage();

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

//#pragma region ¾È¾¸
	/* ============ ¾È¾¸ ============ */
	UPROPERTY(EditAnywhere, Category = "Input", Meta = (AllowPrivateAccess = true))
	class UInputAction* movement_action;

	UPROPERTY(EditAnywhere, Category = "Input", Meta = (AllowPrivateAccess = true))
	class UInputAction* look_action;

	UPROPERTY(EditAnywhere, Category = "Input", Meta = (AllowPrivateAccess = true))
	class UInputAction* jump_action;

	UPROPERTY(EditAnywhere, Category = "Input", Meta = (AllowPrivateAccess = true))
	class UInputAction* attack_action;

	UPROPERTY(EditAnywhere, Category = "Input", Meta = (AllowPrivateAccess = true))
	class UInputAction* equip_action;
	/* ============ ¾È¾¸ ============ */
//#pragma endregion ¾È¾¸

	UPROPERTY(EditAnywhere, Category = "Input", Meta = (AllowPrivateAccess = true))
	class UInputAction* select_slot_action;

	UPROPERTY(EditAnywhere, Category = "Input", Meta = (AllowPrivateAccess = true))
	class UInputAction* inventory_action;

	UPROPERTY(EditAnywhere, Category = "Input", Meta = (AllowPrivateAccess = true))
	class UInputAction* reload_action;

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
};
