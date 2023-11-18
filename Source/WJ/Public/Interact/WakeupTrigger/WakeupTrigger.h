// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interact/InteractActor.h"
#include "WakeupTrigger.generated.h"

/**
 * 
 */
UCLASS()
class WJ_API AWakeupTrigger : public AInteractActor
{
	GENERATED_BODY()
	
public:
	AWakeupTrigger();

public:
	const bool Interact(AActor* _intereacting_actor) noexcept override;

protected:
	void BeginPlay() override;

private:
	void WakeUp() noexcept;
	

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Option", meta=(AllowPrivateAccess="true"))
	class UBoxComponent* trigger_range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Option", meta = (AllowPrivateAccess = "true"))
	FVector		box_component_size;

	TArray<class AEnemy*> enemies;
};
