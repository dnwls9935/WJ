// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/AI/Controller/BTTask_FindPatrolPos.h"
#include "Enemy/AI/Controller/Base_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"


UBTTask_FindPatrolPos::UBTTask_FindPatrolPos()
{
	NodeName = "FindPatrolPos";
}

EBTNodeResult::Type UBTTask_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto current_pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (current_pawn == nullptr)
		return EBTNodeResult::Type::Failed;

	auto navigation_system = UNavigationSystemV1::GetNavigationSystem(current_pawn->GetWorld());
	if(navigation_system == nullptr)
		return EBTNodeResult::Type::Failed;

	auto origin_vector = OwnerComp.GetBlackboardComponent()->GetValueAsVector(ABase_AIController::spawn_position);
	FNavLocation next_patrol;

	if (navigation_system->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0f, next_patrol) == true)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(ABase_AIController::patrol_position, next_patrol.Location);
		return EBTNodeResult::Type::Succeeded;
	}


	return EBTNodeResult::Type::Failed;
}
