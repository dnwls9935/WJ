// Fill out your copyright notice in the Description page of Project Settings.


#include "Interact/WakeupTrigger/WakeupTrigger.h"
#include "Components/BoxComponent.h"
#include "Enemy/Enemy.h"

AWakeupTrigger::AWakeupTrigger()
	: box_component_size(FVector(100, 100, 100))
{
}

const bool AWakeupTrigger::Interact(AActor* _intereacting_actor) noexcept
{
	auto result = Super::Interact(_intereacting_actor);
	if (result == false)
		return false;
	
	WakeUp();

	return true;
}

void AWakeupTrigger::BeginPlay()
{
	Super::BeginPlay();

	auto location = GetActorLocation();
	DrawDebugBox(GetWorld(), location, box_component_size, FColor::Purple, true);

	/* 감지된 엑터들 */
	TArray<FOverlapResult> overlap_results;
	FCollisionQueryParams collision_query_params(NAME_None, false, this);
	auto result = GetWorld()->OverlapMultiByChannel(overlap_results
											, this->GetActorLocation()
											, FQuat::Identity
											, ECollisionChannel::ECC_Pawn
											, FCollisionShape::MakeBox(box_component_size)
											, collision_query_params);

	if (result == true && overlap_results.IsEmpty() == false)
	{
		for (auto const& iter : overlap_results)
		{
			auto actor = iter.GetActor();

			if (actor->Tags.IsEmpty() == true)
				continue;

			if (actor->ActorHasTag(FName("Enemy")) == false)
				continue;

			enemies.AddUnique(Cast<AEnemy>(actor));
		}
	}

}

void AWakeupTrigger::WakeUp() noexcept
{
	for (auto iter : enemies)
		iter->WakeUpEvent(FMath::RandRange(0.1f, 2.5f), interacting_actor);
}
