// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/AI/Controller/Base_AIController.h"
#include "BaseCharacter/BaseCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

const FName ABase_AIController::spawn_position(TEXT("spawn_position"));
const FName ABase_AIController::patrol_position(TEXT("patrol_position"));
const FName ABase_AIController::target_key(TEXT("target"));

ABase_AIController::ABase_AIController()
	: behavior_tree(nullptr)
	, black_board(nullptr)
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> black_board_object(TEXT("/Game/WJ_Project/Character/Enemy/Zombie/AI/BB_Zombie.BB_Zombie"));
	if (black_board_object.Succeeded() == true)
	{
		black_board = black_board_object.Object;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("black board success"));
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> behaivor_tree_object(TEXT("/Game/WJ_Project/Character/Enemy/Zombie/AI/BT_Zombie.BT_Zombie"));
	if (behaivor_tree_object.Succeeded() == true)
	{
		behavior_tree = behaivor_tree_object.Object;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("behavior success"));
	}

	b = false;

}

void ABase_AIController::OnPossess(APawn* _pawn)
{
	Super::OnPossess(_pawn);

	UBlackboardComponent* blackboard = Blackboard;
	if (UseBlackboard(black_board, blackboard) == true)
	{
		Blackboard.Get()->SetValueAsVector(spawn_position, _pawn->GetActorLocation());
		if (RunBehaviorTree(behavior_tree) == false)
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("RunBehaviorTree is false"));
	}

}

void ABase_AIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void ABase_AIController::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABase_AIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
