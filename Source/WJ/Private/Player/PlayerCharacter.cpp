// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Engine/Classes/Components/InputComponent.h"
#include "UObject/Object.h"
#include "Misc/OutputDeviceNull.h"
#include "Equip/Gun/Gun.h"
#include "Player/SlotComponent.h"
#include "Kismet/GameplayStatics.h"

APlayerCharacter::APlayerCharacter()
	: spring_arm(nullptr)
	, camera(nullptr)
	, player_input_mapping_context(nullptr)
	, movement_action(nullptr)
	, look_action(nullptr)
	, jump_action(nullptr)
	, reload_action(nullptr)
	, attack_action(nullptr)
	, attack_montage(nullptr)
	, equip_action(nullptr)
	, select_slot_action(nullptr)
	, inventory_action(nullptr)
	, equip_weapon(nullptr)
	, is_zoomm(false)
{
	slots_component = CreateDefaultSubobject<USlotComponent>(TEXT("Slots"));
	actor_type = ACTOR_TYPE::PLAYER;
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//PlayerInputComponent->BindAction(TEXT(""), EInputEvent::IE_Pressed, this, );


	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//EnhancedInputComponent->BindAction(attack_action, ETriggerEvent::Started, this, &APlayerCharacter::SelectSlotInputEvnet);
		EnhancedInputComponent->BindAction(select_slot_action, ETriggerEvent::Started, this, &APlayerCharacter::SelectSlotInputEvnet);
		EnhancedInputComponent->BindAction(inventory_action, ETriggerEvent::Started, this, &APlayerCharacter::InventoryInputEvent);
		EnhancedInputComponent->BindAction(reload_action, ETriggerEvent::Started, this, &APlayerCharacter::Reload);
	}
}

void APlayerCharacter::SetEquipWeqpon(AGun* _weapon) noexcept
{
	//_weapon->SetActorHiddenInGame(false);
	//
	if(equip_weapon != nullptr)
		equip_weapon->SetActorHiddenInGame(true);

	_weapon->SetActorHiddenInGame(false);
	_weapon->SetOwnerPlayer(this);
	equip_weapon = _weapon;
}

void APlayerCharacter::ClearEquipWeapon() noexcept
{
	if (equip_weapon != nullptr)
		equip_weapon->SetActorHiddenInGame(true);

	equip_weapon = nullptr;
}


void APlayerCharacter::CameraShaking() noexcept
{
	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(shake_classes, 1.0f);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();


	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			Subsystem->AddMappingContext(player_input_mapping_context, 0);
	}
}

void APlayerCharacter::Attack() noexcept
{
	Super::Attack();
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation = FRotator(0.0f,0.0f/* Rotation.Yaw*/
		, 0.0f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, MovementVector.Y);

	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerPitchInput(LookAxisVector.Y);
	AddControllerYawInput(LookAxisVector.X);
}

void APlayerCharacter::Equip(const FInputActionValue& Value)
{
}

void APlayerCharacter::PlayAttackMontage()
{
}

void APlayerCharacter::Die() noexcept
{
	Super::Die();

}

void APlayerCharacter::Hit(const float _damage_amount) noexcept
{
	Super::Hit(_damage_amount);
	
}

void APlayerCharacter::Reload(const FInputActionValue& Value)
{
	/* Camera Shake Test */
	if (equip_weapon->CanReload() == false)
		return;

	auto value = Value.Get<FVector>().X;

	if (equip_weapon == nullptr)
	{
		current_weapon_type_reload_montage = nullptr;
		return;
	}

	switch (equip_weapon->GetWeaponType())
	{
	case WEAPON_STATUS::ONE_HAND_PISTOL:
		current_weapon_type_reload_montage = one_hand_pistol_reload_montage;
		break;
	case WEAPON_STATUS::TWO_HAND_PISTOL:
		break;
	case WEAPON_STATUS::RIFLE:
		current_weapon_type_reload_montage = rifle_reload_montage;
		break;
	case WEAPON_STATUS::NONE:
	default:
		current_weapon_type_reload_montage = current_weapon_type_reload_montage;
		break;
	}

	Reloading();
}

void APlayerCharacter::SelectSlotInputEvnet(const FInputActionValue& _value) noexcept
{
	auto value = _value.Get<FVector>().X;
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT("SelectSlotInputEvnet Event!! : %f"), value));

	FOutputDeviceNull ODN;
	this->CallFunctionByNameWithArguments(*FString::Printf(TEXT("BPISetOverlayStateEvent %d"), static_cast<int>(value)), ODN, nullptr, true);
}

void APlayerCharacter::InventoryInputEvent(const FInputActionValue& value) noexcept
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("InventoryInputEvent Event!!"));
}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	auto sum = current_health - DamageAmount;

	if (sum <= 0)
		Die();
	else
		Hit(sum);

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, FString::Printf(TEXT("%f"), current_health));
	return current_health;
}

