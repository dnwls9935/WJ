// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/WJGameMode.h"
#include "Kismet/GameplayStatics.h"
#include <Blueprint/UserWidget.h>
#include "Blueprint/WidgetBlueprintLibrary.h"

AWJGameMode::AWJGameMode()
	: level_on(true)
	, ending(false)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWJGameMode::ChangeHUD(TSubclassOf<UUserWidget> _widget_class) noexcept
{
	if (current_widget != nullptr)
	{
		current_widget->RemoveFromViewport();
		current_widget = nullptr;
	}
	
	if (_widget_class != nullptr)
	{
		current_widget = CreateWidget(GetWorld(), _widget_class);
		if (current_widget != nullptr)
		{
			current_widget->AddToViewport();
		}
	}

}

void AWJGameMode::ChangeLevel(FName _level_name) noexcept
{
	UGameplayStatics::OpenLevel(GetWorld(), _level_name);

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Change Level!!"));
}

void AWJGameMode::AddDefenseActor(AActor* _actor) noexcept
{
	defense_actor.Add(_actor);
	level_on = false;
}

void AWJGameMode::DeleteDefenseActor(AActor* _actor) noexcept
{
	auto index = defense_actor.Find(_actor);
	if (index == INDEX_NONE)
		return;

	defense_actor.RemoveAt(index);
}

void AWJGameMode::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());
	//ChangeHUD(start_widget_class);
	FindPlayerStart(GetWorld()->GetFirstPlayerController());
}

void AWJGameMode::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);
	if (level_on == true)
		return;

	if (ending == true)
	{
		auto timer = GetWorldTimerManager().GetTimerElapsed(end_timer);
		GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Purple, *FString::Printf(TEXT("%f"), timer));

		if (timer < 0)
		{
			ChangeLevel(FName("MainMenu"));
			return;
		}
		return;
	}

	if (GetDefenActorSize() <= 0)
	{
		ChangeHUD(finish_widget_class);
		GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
		GetWorldTimerManager().SetTimer(end_timer , 3.0f , false);
		ending = true;
	}

}
