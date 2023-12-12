// Fill out your copyright notice in the Description page of Project Settings.


#include "Interact/AmmoBox/AmmoBox.h"
#include "Player/PlayerCharacter.h"
#include "UI/ItemFocusComponent.h"
#include "Components/WidgetComponent.h"

AAmmoBox::AAmmoBox()
{
	static_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	static_mesh->SetupAttachment(GetRootComponent());

	skeletal_mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	skeletal_mesh->SetupAttachment(GetRootComponent());

	interact_type = INTERACT_TYPE::AMMO_BOX;

	widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("UI"));
	widget->SetupAttachment(static_mesh);
	widget->SetWidgetSpace(EWidgetSpace::Screen);
}

const bool AAmmoBox::Interact(AActor* _intereacting_actor) noexcept
{
	Super::Interact(_intereacting_actor);
	if (_intereacting_actor == nullptr)
		return false;

	auto cast_actor = Cast<APlayerCharacter>(interacting_actor);
	if (cast_actor == nullptr)
		return false;

	/* 대충 사운드 출력 */
	return true;
}

void AAmmoBox::BeginPlay()
{
	Super::BeginPlay();
}

void AAmmoBox::Tick(float _deltaTime)
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

void AAmmoBox::FocusOn(const bool b) noexcept
{
	Super::FocusOn(b);
	widget->SetVisibility(b);

	if (b == true)
	{
		static_mesh->SetScalarParameterValueOnMaterials(TEXT("FresnelMul"), 500);
	}
	else
	{
		static_mesh->SetScalarParameterValueOnMaterials(TEXT("FresnelMul"), 0);
	}
}
