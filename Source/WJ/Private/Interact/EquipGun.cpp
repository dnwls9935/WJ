// Fill out your copyright notice in the Description page of Project Settings.


#include "Interact/EquipGun.h"
#include "Player/PlayerCharacter.h"
#include "UI/ItemFocusComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/ItemDecription.h"

AEquipGun::AEquipGun()
{
	skeletal_mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	skeletal_mesh->SetupAttachment(GetRootComponent());

	interact_type = INTERACT_TYPE::EQUIP_WEAPON;

	widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("UI"));
	widget->SetupAttachment(skeletal_mesh);
	widget->SetWidgetSpace(EWidgetSpace::Screen);

	type = WEAPON_TYPE::NONE;
}

const bool AEquipGun::Interact(AActor* _intereacting_actor) noexcept
{
	Super::Interact(_intereacting_actor);
	if (_intereacting_actor == nullptr)
		return false;

	auto cast_actor = Cast<APlayerCharacter>(interacting_actor);
	if (cast_actor == nullptr)
		return false;

	cast_actor->AddSlot(type);

	/* 대충 사운드 출력 */
	return true;
}

void AEquipGun::BeginPlay()
{
	Super::BeginPlay();

	auto cast_class = Cast<UItemDecription>(widget->GetUserWidgetObject());
	if (cast_class == nullptr)
		return;

	switch (type)
	{
	case WEAPON_TYPE::PISTOL:
		cast_class->SetDescriptionTitle("One Hand Pistol");
		break;
	case WEAPON_TYPE::RIFLE:
		cast_class->SetDescriptionTitle("Rifle");
		break;
	case WEAPON_TYPE::NONE:
		break;
	default:
		break;
	}
}

void AEquipGun::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);

	auto actor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (actor == nullptr)
		return;

	auto cast_actor = Cast<APlayerCharacter>(actor);
	if (cast_actor == nullptr)
		return;

	auto focus_actor = cast_actor->GetFocusActor();
	if (focus_actor != nullptr && focus_actor == this)
		FocusOn(true);
	else
		FocusOn(false);
}

void AEquipGun::FocusOn(const bool b) noexcept
{
	Super::FocusOn(b);
	widget->SetVisibility(b);
	
	if (b == true)
	{
		skeletal_mesh->SetScalarParameterValueOnMaterials(TEXT("FresnelMul"), 500);
	}
	else
	{
		skeletal_mesh->SetScalarParameterValueOnMaterials(TEXT("FresnelMul"), 0);
	}
}
