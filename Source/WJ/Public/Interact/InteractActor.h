// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "InteractActor.generated.h"

UCLASS()
class WJ_API AInteractActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AInteractActor();

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual const bool Interact(AActor* _interacting_actor) noexcept;

	FORCEINLINE const AActor* GetInteractingActor() noexcept { return interacting_actor; }
	FORCEINLINE void SetInteractingActor(AActor* _interacting_actor) noexcept { interacting_actor = _interacting_actor; }

protected:
	virtual void BeginPlay() override;



protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Option", meta = (AllowPrivateAccess = "true"))
	bool is_interact;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Option", meta = (AllowPrivateAccess = "true"))
	AActor* interacting_actor;
};
