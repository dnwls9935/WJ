// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interact/InteractActor.h"
#include "InteractButton.generated.h"

/**
 * 
 */
UCLASS()
class WJ_API AInteractButton : public AInteractActor
{
	GENERATED_BODY()

public:
	AInteractButton();

public:
	const bool Interact(AActor* _intereacting_actor) noexcept override;
	void Tick(float _deltaTime) override;
	void FocusOn(const bool _b) noexcept;

protected:
	void BeginPlay() override;


private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* static_mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* skeletal_mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* widget;

};
