// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEnd_Delegate);

UCLASS()
class WJ_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Attack() noexcept;

	UFUNCTION()
	virtual void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	void PostInitializeComponents() override;

protected:
	virtual void BeginPlay() override;

public:
	FOnAttackEnd_Delegate on_attack_end;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Status", meta=(AllowPrivateAccess="true"))
	float max_health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status", meta = (AllowPrivateAccess = "true"))
	float current_health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	bool	is_attack;

	UPROPERTY()
	class UBaseAnimInstance* animinstance;

};
