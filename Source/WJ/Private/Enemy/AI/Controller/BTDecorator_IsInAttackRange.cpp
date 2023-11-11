// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/AI/Controller/BTDecorator_IsInAttackRange.h"
#include "Enemy/AI/Controller/Base_AIController.h"
#include "BaseCharacter/BaseCharacter.h"
#include "Enemy/Enemy.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	auto result = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	const auto controlling_pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (controlling_pawn == nullptr)
		return false;


	const auto target = Cast<ACharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ABase_AIController::target_key));
	
	if (target == nullptr)
		return false;

	result = (target->GetDistanceTo(controlling_pawn) <= 200.0f);

	return result;
}
