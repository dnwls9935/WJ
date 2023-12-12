// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGameHUD.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Equip/Gun/Gun.h"

void UInGameHUD::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	/*aim_top_bar = Cast<UImage>(GetWidgetFromName(TEXT("aim_top")));
	aim_botom_bar = Cast<UImage>(GetWidgetFromName(TEXT("aim_bottom")));
	aim_right_bar = Cast<UImage>(GetWidgetFromName(TEXT("aim_right")));
	aim_left_bar = Cast<UImage>(GetWidgetFromName(TEXT("aim_left")));*/

	circle_info = Cast<UImage>(GetWidgetFromName(TEXT("circle")));
	dot_info = Cast<UImage>(GetWidgetFromName(TEXT("dot")));

	current_ammo_info = Cast<UTextBlock>(GetWidgetFromName(TEXT("current_ammo")));
	current_magazine_info = Cast<UTextBlock>(GetWidgetFromName(TEXT("current_magazine")));
}

void UInGameHUD::UpdateAmmoAndMagazine(AGun* _gun) noexcept
{
	if (_gun == nullptr)
	{
		if (current_ammo_info != nullptr)
			current_ammo_info->SetText(FText::FromString(FString::Printf(TEXT("-"))));

		if (current_magazine_info != nullptr)
			current_magazine_info->SetText(FText::FromString(FString::Printf(TEXT("-"))));
	}
	else
	{
		if(current_ammo_info != nullptr)
			current_ammo_info->SetText(FText::FromString(FString::Printf(TEXT("%d"), _gun->GetCurrentAmmo())));

		if(current_magazine_info != nullptr)
			current_magazine_info->SetText(FText::FromString(FString::Printf(TEXT("%d"), _gun->GetCurrentMagazine())));
	}
}

void UInGameHUD::UpdateAimFocus(const bool _b) noexcept
{
	FLinearColor color;
	if (_b == true)
	{
		color.R = 1;
		color.G = 0;
		color.B = 0;
		color.A = 1;
	}
	else
	{
		color.R = 1;
		color.G = 1;
		color.B = 1;
		color.A = 1;
	}

	circle_info->Brush.OutlineSettings.Color = color;
	dot_info->Brush.OutlineSettings.Color = color;
}

bool UInGameHUD::Initialize()
{
	Super::Initialize();
	UpdateAmmoAndMagazine(nullptr);

	return true;
}
