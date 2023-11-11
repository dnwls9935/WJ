// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interact/InteractActor.h"
#include "Math/Vector.h"
#include "Spawning.generated.h"

/**
 * 
 */
UCLASS()
class WJ_API ASpawning : public AInteractActor
{
	GENERATED_BODY()
	
public:
	ASpawning();
	
public:
	const bool Interact(AActor* _intereacting_actor) noexcept override;

private:
	void Spawning() noexcept;

protected:
	void BeginPlay() override;


private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Option", meta=(AllowPrivateAccess="true"))
	FVector	range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Option", meta = (AllowPrivateAccess = "true"))
	int spawn_count;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Time", meta = (AllowPrivateAccess = "true"))
	float spawn_time;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawn Time", meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> spawning_actors_list;

	FTimerHandle spawn_timer;

	int current_count;
};
