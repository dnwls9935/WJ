// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ItemFocusComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UItemFocusComponent::UItemFocusComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	scene_component = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));

	widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("UI"));
	static ConstructorHelpers::FClassFinder<UUserWidget> ui(TEXT("/Game/WJ_Project/UI/BP_Desciption.BP_Desciption_C"));
	if (ui.Succeeded() == true)
	{
		widget->SetWidgetClass(ui.Class);
	}

	widget->SetupAttachment(scene_component);

	// ...
}


// Called when the game starts
void UItemFocusComponent::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UItemFocusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

