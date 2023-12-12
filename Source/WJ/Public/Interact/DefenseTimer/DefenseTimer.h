// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interact/InteractActor.h"
#include "DefenseTimer.generated.h"

/**
 * 
 */
UCLASS()
class WJ_API ADefenseTimer : public AInteractActor
{
	GENERATED_BODY()

public:
	ADefenseTimer();

public:
	const bool Interact(AActor* _intereacting_actor) noexcept override;

	void Tick(float _deltaTime) override;

private:
	void Spawning() noexcept;

protected:
	void BeginPlay() override;


private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Option", meta = (AllowPrivateAccess = "true"))
	FVector	range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Time", meta = (AllowPrivateAccess = "true"))
	float spawn_time;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defense Time", meta = (AllowPrivateAccess = "true"))
	float defense_time;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawn Time", meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> spawning_actors_list;

	FTimerHandle defense_timer;
	FTimerHandle spawn_timer;

	bool is_defense_begin;
};
