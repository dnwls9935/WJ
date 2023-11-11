// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WJ_API UInteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInteractComponent();
	
public:
	UFUNCTION(BlueprintCallable)
	void PlayInteract(AActor* _interacting_actor) noexcept;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	FORCEINLINE bool GetIsPlayInteract() const noexcept {return is_play_interact;}

	UFUNCTION()
	FORCEINLINE void SetIsPlayInteract(const bool _b) noexcept { is_play_interact = _b; }

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interact Actors", meta=(AllowPrivateAccess="true"))
	TArray<class AInteractActor*> interactive_actors;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Option", meta = (AllowPrivateAccess = "true"))
	bool is_play_interact;
};
