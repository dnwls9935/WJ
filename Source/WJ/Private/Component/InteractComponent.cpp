// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/InteractComponent.h"
#include "Interact/InteractActor.h"

// Sets default values for this component's properties
UInteractComponent::UInteractComponent()
	: is_play_interact(false)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteractComponent::PlayInteract(AActor* _interacting_actor) noexcept
{
	if (interactive_actors.IsEmpty() == true)
		return;

	if (GetIsPlayInteract() == true)
		return;

	SetIsPlayInteract(true);

	for (auto iter : interactive_actors)
		iter->Interact(_interacting_actor);
}


void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);



}