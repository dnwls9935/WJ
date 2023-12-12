// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class WJ_API UInGameHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeOnInitialized() override;

	void UpdateAmmoAndMagazine(class AGun* _gun) noexcept;

	void UpdateAimFocus(const bool _b) noexcept;

	bool Initialize() override;

private:
	/*UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Info", meta = (AllowPrivateAccess = "true"))
	class UImage*		aim_top_bar;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Info", meta = (AllowPrivateAccess = "true"))
	class UImage*		aim_botom_bar;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Info", meta = (AllowPrivateAccess = "true"))
	class UImage*		aim_right_bar;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Info", meta = (AllowPrivateAccess = "true"))
	class UImage*		aim_left_bar;*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Info", meta = (AllowPrivateAccess = "true"))
	class UImage* circle_info;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Info", meta = (AllowPrivateAccess = "true"))
	class UImage* dot_info;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Info", meta = (AllowPrivateAccess = "true"))
	class UTextBlock*		current_ammo_info;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Info", meta = (AllowPrivateAccess = "true"))
	class UTextBlock*		current_magazine_info;
};
