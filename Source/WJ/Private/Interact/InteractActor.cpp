// Fill out your copyright notice in the Description page of Project Settings.


#include "Interact/InteractActor.h"
#include "Player/PlayerCharacter.h"

// Sets default values
AInteractActor::AInteractActor()
	: actor_type(ACTOR_TYPE::INTERACT)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

const bool AInteractActor::Interact(AActor* _interacting_actor) noexcept
{
	if (Cast<APlayerCharacter>(_interacting_actor) == nullptr)
		return false;

	is_interact = true;
	SetInteractingActor(_interacting_actor);

	return true;
}

void AInteractActor::FocusOn(const bool b) noexcept
{
}

// Called when the game starts or when spawned
void AInteractActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

