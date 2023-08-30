// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Base_AIController.generated.h"

/**
 * 
 */
UCLASS()
class WJ_API ABase_AIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ABase_AIController();

public:
	virtual void OnPossess(class APawn* _pawn) override;
	virtual void OnUnPossess() override;

public:
	static const FName spawn_position;
	static const FName patrol_position;
	static const FName target_key;

private:
	UPROPERTY()
	class UBehaviorTree*		behavior_tree;

	UPROPERTY()
	class UBlackboardData*		black_board;
};
