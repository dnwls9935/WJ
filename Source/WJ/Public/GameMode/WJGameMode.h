// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "../UI/InGameHUD.h"
#include "WJGameMode.generated.h"

/**
 * 
 */
UCLASS()
class WJ_API AWJGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category="HUD")
	void ChangeHUD(TSubclassOf<UUserWidget> _widget_class) noexcept;

public:
	template<typename T>
	void UpdateCurrentWidgetInfo(T _t) noexcept;


	FORCEINLINE class UInGameHUD* GetCurrentHUD() { return Cast<UInGameHUD>(current_widget); };

private:
	void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> start_widget_class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HUD", meta=(AllowPrivateAccess="true"))
	class UUserWidget* current_widget;
};

template<typename T>
inline void AWJGameMode::UpdateCurrentWidgetInfo(T _t) noexcept
{
	auto cast_widget = Cast<UInGameHUD>(current_widget);
	if (cast_widget == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Red, TEXT("current_widget is nullptr"));
	}
	else
	{
		cast_widget->UpdateAmmoAndMagazine(nullptr);
	}
}


template<>
inline void AWJGameMode::UpdateCurrentWidgetInfo(class AGun* _gun) noexcept
{
	auto cast_widget = Cast<UInGameHUD>(current_widget);
	if (cast_widget == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Red, TEXT("current_widget is nullptr"));
	}
	else
		cast_widget->UpdateAmmoAndMagazine(_gun);
}