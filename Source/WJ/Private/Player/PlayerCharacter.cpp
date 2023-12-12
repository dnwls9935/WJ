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
#include "GameMode/WJGameMode.h"
#include "Interact/InteractActor.h"
#include "Interact/AmmoBox/AmmoBox.h"
#include "GameMode/WJGameMode.h"
#include "Enemy/Enemy.h"
#include "Interact/Turret/Turret.h"

APlayerCharacter::APlayerCharacter()
	: spring_arm(nullptr)
	, camera(nullptr)
	, player_input_mapping_context(nullptr)
	, reload_action(nullptr)
	, attack_montage(nullptr)
	, select_slot_action(nullptr)
	, inventory_action(nullptr)
	, equip_weapon(nullptr)
	, is_zoomm(false)
	, current_movement_delta(0)
	, cross_hair_spread_multiplier(0)
	, corss_hair_velocity_factor(0)
	, interact_distance(650)
	, is_interacted(false)
	, attach_turret(nullptr)
{
	slots_component = CreateDefaultSubobject<USlotComponent>(TEXT("Slots"));
	actor_type = ACTOR_TYPE::PLAYER;


	interact_point = CreateDefaultSubobject<USceneComponent>(TEXT("Interact Point"));
	interact_point->SetupAttachment(GetRootComponent());
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
		EnhancedInputComponent->BindAction(flash_action, ETriggerEvent::Started, this, &APlayerCharacter::Flash);
		EnhancedInputComponent->BindAction(interact_action, ETriggerEvent::Started, this, &APlayerCharacter::Interact);
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
	equip_weapon->UpdateWeaponInfoToHUD();
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

void APlayerCharacter::EquipStateIsNone() noexcept
{
	auto game_mode = UGameplayStatics::GetGameMode(GetWorld());
	if (game_mode != nullptr)
	{
		if(cast_game_mode != nullptr) cast_game_mode->UpdateCurrentWidgetInfo(nullptr);
	}
}

void APlayerCharacter::Tick(float _delta_time)
{
	Super::Tick(_delta_time);

	if(cast_game_mode->GetCurrentHUD() != nullptr) cast_game_mode->GetCurrentHUD()->UpdateAimFocus(false);
	focus_actor = nullptr;

	if (/*is_zoomm == true && */camera_actor != nullptr)
	{
		FHitResult hit_result;

		auto start = camera_actor->GetActorLocation();
		auto end = start + (camera_actor->GetActorForwardVector() * 3000.0f);

		if (GetWorld()->LineTraceSingleByChannel(hit_result, start, end, ECollisionChannel::ECC_Pawn))
		{
			if (hit_result.GetActor() == nullptr)
				return;

			if (hit_result.GetActor()->Tags.IsEmpty() == true)
				return;

			if (hit_result.GetActor()->ActorHasTag(FName("Enemy")) == true)
			{
				auto hud = cast_game_mode->GetCurrentHUD();
				if(hud != nullptr)
					hud->UpdateAimFocus(true);

				return;
			}
			if (( hit_result.GetActor()->ActorHasTag(FName("AmmoBox")) == true 
				|| hit_result.GetActor()->ActorHasTag(FName("EquipGun")) == true
				|| hit_result.GetActor()->ActorHasTag(FName("Button")) == true )
				&& hit_result.Distance <= interact_distance)
			{

				focus_actor = hit_result.GetActor();
				return;
			}
			
			return;
		}
	}
}

void APlayerCharacter::AddSlot(WEAPON_TYPE _type) noexcept
{
	slots_component->Add(_type);


	if (slots_component->GetSize() == 1)
		SelectSlot(1);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();


	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			Subsystem->AddMappingContext(player_input_mapping_context, 0);
	}

	FOutputDeviceNull ODN;
	this->CallFunctionByNameWithArguments(*FString::Printf(TEXT("BPISetOverlayStateEvent %d"), 1), ODN, nullptr, true);


	auto game_mode = UGameplayStatics::GetGameMode(GetWorld());
	if (game_mode != nullptr)
	{
		cast_game_mode = Cast<AWJGameMode>(game_mode);
		cast_game_mode->UpdateCurrentWidgetInfo(nullptr);
	}
}

void APlayerCharacter::Attack() noexcept
{
	Super::Attack();
}

void APlayerCharacter::Move(float _speed) noexcept
{
	current_movement_delta = _speed;

	FVector2D Input(0.f, 600.f);
	FVector2D Output(0.f, current_movement_delta);
	corss_hair_velocity_factor = FMath::GetMappedRangeValueClamped(Input, Output, 150.f);

	cross_hair_spread_multiplier = 0.5f + corss_hair_velocity_factor; // 0.5~1.5
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

void APlayerCharacter::Flash(const FInputActionValue& Value)
{

	if(equip_weapon != nullptr)
		equip_weapon->SetFlash();
}

void APlayerCharacter::Interact(const FInputActionValue& Value)
{
	auto camera_manager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	FVector start = camera_manager->GetCameraLocation();
	FVector end = camera_manager->GetActorForwardVector();

	end *= interact_distance;

	if (is_interacted == true)
	{
		is_interacted = attach_turret->AttachActor(false, this);
		return;
	}


	FHitResult hit_result;
	bool b = GetWorld()->LineTraceSingleByChannel(hit_result, start, start + end, ECollisionChannel::ECC_Visibility);

	if (b == true)
	{
		auto cast_actor = Cast<AInteractActor>(hit_result.GetActor());
		if (cast_actor == nullptr)
			return;

		auto type = cast_actor->GetInteractType();
		switch (type)
		{
		case INTERACT_TYPE::AMMO_BOX:
		{
			const auto result = cast_actor->Interact(this);
			if (result == true)
			{
				if (equip_weapon != nullptr && equip_weapon->CanAddMagazine() == true)
				{
					equip_weapon->AddMagazine();
					hit_result.GetActor()->Destroy();
				}
			}
		}
			break;
		case INTERACT_TYPE::EQUIP_WEAPON:
		{
			const auto result = cast_actor->Interact(this);
			if (result == true)
			{
				hit_result.GetActor()->Destroy();
			}
		}
			break;
		case INTERACT_TYPE::BUTTON:
		{
			const auto result = cast_actor->Interact(this);
		}
			break;
		case INTERACT_TYPE::TURRET:
		{
			const auto result = cast_actor->Interact(this);
			is_interacted = Cast<ATurret>(cast_actor)->AttachActor(true, this);
			attach_turret = Cast<ATurret>(cast_actor);
		}
			break;
		case INTERACT_TYPE::NONE:
		default:
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Interact Type is null!!!"));
			break;
		}
	}
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
	if (equip_weapon == nullptr)
		return;

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
	SelectSlot(static_cast<int>(value));
}

void APlayerCharacter::InventoryInputEvent(const FInputActionValue& value) noexcept
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("InventoryInputEvent Event!!"));
	//cast_game_mode->ChangeLevel(FName("Scene_0"));
}

void APlayerCharacter::SelectSlot(const int _index) noexcept
{
	FOutputDeviceNull ODN;
	this->CallFunctionByNameWithArguments(*FString::Printf(TEXT("BPISetOverlayStateEvent %d"), _index), ODN, nullptr, true);
}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	auto sum = current_health - DamageAmount;

	if (Cast<AEnemy>(DamageCauser) == nullptr)
		return current_health;

	if (sum <= 0)
		Die();
	else
		Hit(sum);

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, FString::Printf(TEXT("%f"), current_health));
	return current_health;
}

