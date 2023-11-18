
#include "Player/SlotComponent.h"
#include "Equip/Gun/Gun.h"
#include "Engine/GameInstance.h"
#include "GameMode/WJ_GameSubSystem.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Kismet/GameplayStatics.h"

USlotComponent::USlotComponent()
	: current_index(0)
{
	PrimaryComponentTick.bCanEverTick = true;

}


void USlotComponent::Add(const WEAPON_TYPE _type) noexcept
{
	if (_type == WEAPON_TYPE::NONE)
		return;

	slots.Add(_type);
}

// Called when the game starts
void USlotComponent::BeginPlay()
{
	Super::BeginPlay();

	Add(WEAPON_TYPE::RIFLE);
	Add(WEAPON_TYPE::PISTOL);
	Add(WEAPON_TYPE::PISTOL);
}


// Called every frame
void USlotComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, FString::Printf(TEXT("tick slot index 1 %s  /  index 2 %s  /  index 3 %s  /  index 4 %s"), *slots[0]->GetName(), *slots[1]->GetName(), *slots[2]->GetName(), *slots[3]->GetName()));	// ...
}

void USlotComponent::SetItemToSlot(int _slot_index, WEAPON_TYPE _weapon) noexcept
{
	if (_slot_index < 0 || _slot_index > 5)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("error slot index is %d"), _slot_index));
		return;
	}

	slots[_slot_index] = _weapon;
}

WEAPON_STATUS USlotComponent::GetSelectedSlotItem(const int _index) noexcept
{
	auto index = _index - 1;
	if (index < 0 || index > 5)
		return WEAPON_STATUS::NONE;

	auto size = slots.Num();
	if (size <= index)
		return WEAPON_STATUS::NONE;

	auto value = slots[index];
	if (value == WEAPON_TYPE::NONE)
		return WEAPON_STATUS::NONE;

	UGameInstance* game_instance = UGameplayStatics::GetGameInstance(GetWorld());
	auto my_subsytem = game_instance->GetSubsystem<UWJ_GameSubSystem>();

	return my_subsytem->GetWeaponStatus(value);
}

