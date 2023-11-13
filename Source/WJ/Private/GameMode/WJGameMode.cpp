// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/WJGameMode.h"
#include <Blueprint/UserWidget.h>

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

void AWJGameMode::BeginPlay()
{
	Super::BeginPlay();
	ChangeHUD(start_widget_class);
}
