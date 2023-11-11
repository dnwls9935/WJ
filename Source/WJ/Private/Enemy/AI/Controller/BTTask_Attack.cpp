// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/AI/Controller/BTTask_Attack.h"
#include "BaseCharacter/BaseCharacter.h"
#include "Enemy/AI/Controller/Base_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/Enemy.h"

UBTTask_Attack::UBTTask_Attack()
	: is_attaking(false)
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto character = Cast<AEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (character == nullptr)
		return EBTNodeResult::Failed;

	character->Attack();
	is_attaking = false;

	character->on_attack_end.AddLambda([this]() -> void
				{
					//is_attaking = false;
				});

	//auto target =  OwnerComp.GetBlackboardComponent()->GetValueAsObject(ABase_AIController::target_key);
	//OwnerComp.GetAIOwner()->MoveTo(Cast<ABaseCharacter>(target), 3);

	return EBTNodeResult::Type::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSecond)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSecond);


	auto castPawn = Cast<AEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (castPawn != nullptr && castPawn->CanAttack() == false)
	{
		castPawn->Attack();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
