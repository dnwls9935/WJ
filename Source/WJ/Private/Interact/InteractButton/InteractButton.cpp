// Fill out your copyright notice in the Description page of Project Settings.


#include "Interact/InteractButton/InteractButton.h"
#include "UObject/Object.h"
#include "Misc/OutputDeviceNull.h"
#include "UI/ItemFocusComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/ItemDecription.h"
#include "Player/PlayerCharacter.h"

AInteractButton::AInteractButton()
{
	skeletal_mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	skeletal_mesh->SetupAttachment(GetRootComponent());

	widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("UI"));
	widget->SetupAttachment(skeletal_mesh);
	widget->SetWidgetSpace(EWidgetSpace::Screen);

}

const bool AInteractButton::Interact(AActor* _intereacting_actor) noexcept
{
	if(is_interact == true)
		return is_interact;

	Super::Interact(_intereacting_actor);
	
	FOutputDeviceNull ODN;
	this->CallFunctionByNameWithArguments(*FString(TEXT("InteractingButton")), ODN, nullptr, true);

	is_interact = true;

	auto cast_class = Cast<UItemDecription>(widget->GetUserWidgetObject());
	if (cast_class == nullptr)
		return false;

	cast_class->SetDescriptionTitle("Defense!!");

	return is_interact;
}

void AInteractButton::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);

	if (is_interact == true)
		return;

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

void AInteractButton::FocusOn(const bool _b) noexcept
{
	Super::FocusOn(_b);

	widget->SetVisibility(_b);

	if (_b == true)
	{
		skeletal_mesh->SetScalarParameterValueOnMaterials(TEXT("FresnelMul"), 500);
	}
	else
	{
		skeletal_mesh->SetScalarParameterValueOnMaterials(TEXT("FresnelMul"), 0);
	}
}

void AInteractButton::BeginPlay()
{
	Super::BeginPlay();

	auto cast_class = Cast<UItemDecription>(widget->GetUserWidgetObject());
	if (cast_class == nullptr)
		return;

	cast_class->SetDescriptionTitle("Press!!");
}
