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
	AWJGameMode();
	
public:
	UFUNCTION(BlueprintCallable, Category="HUD")
	void ChangeHUD(TSubclassOf<UUserWidget> _widget_class) noexcept;

	UFUNCTION(BlueprintCallable)
	void ChangeLevel(FName _level_name) noexcept;

	template<typename T>
	void UpdateCurrentWidgetInfo(T _t) noexcept;

	FORCEINLINE class UInGameHUD* GetCurrentHUD() { return Cast<UInGameHUD>(current_widget); }

	void AddDefenseActor(class AActor* _actor) noexcept;
	void DeleteDefenseActor(class AActor* _actor) noexcept;

	FORCEINLINE const bool GetIsDefenseActorAlive() const noexcept { return defense_actor.IsEmpty(); }
	FORCEINLINE const auto GetDefenActorSize() const noexcept { return defense_actor.Num(); }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool GetGameEnd() const noexcept { return level_on; }


private:
	void BeginPlay() override;
	void Tick(float _deltaTime) override;


private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> start_widget_class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> finish_widget_class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HUD", meta=(AllowPrivateAccess="true"))
	class UUserWidget* current_widget;

	TArray<class AActor*> defense_actor;

	bool level_on;

	FTimerHandle end_timer;

	bool ending;
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