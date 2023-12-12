
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Equip/Gun/Gun.h"
#include "SlotComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WJ_API USlotComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USlotComponent();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "slot")
	void SetItemToSlot(int _slot_index, WEAPON_TYPE _weapon) noexcept;

	UFUNCTION(BlueprintCallable, Category ="slot")
	FORCEINLINE WEAPON_STATUS GetSelectedSlotItem(const int _index)	noexcept;
	
	UFUNCTION(BlueprintCallable, Category = "slot")
	FORCEINLINE int GetCurrentIndex() const noexcept { return current_index; }

	UFUNCTION(BlueprintCallable, Category = "slot")
	void SetCurrentIndex(const int _index) noexcept { current_index = _index; }

	UFUNCTION(BlueprintCallable, Category = "slot")
	void Add(const WEAPON_TYPE _type) noexcept;

	UFUNCTION(BlueprintCallable, Category = "slot")
	FORCEINLINE int32 GetSize() const noexcept { return slots.Num(); }

protected:
	virtual void BeginPlay() override;


private: 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot", meta = (AllowPrivateAccess = "true"))
	TArray<WEAPON_TYPE>		slots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot", meta = (AllowPrivateAccess = "true"))
	int current_index;
};
