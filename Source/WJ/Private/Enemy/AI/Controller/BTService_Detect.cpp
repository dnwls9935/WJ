// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/AI/Controller/BTService_Detect.h"
#include "Enemy/AI/Controller/Base_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"


UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto control_pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (control_pawn == nullptr)
		return;

	auto world = control_pawn->GetWorld();
	if (world == nullptr)
		return;

	/* 감지된 엑터들 */
	TArray<FOverlapResult> overlap_results;
	FCollisionQueryParams collision_query_params(NAME_None, false, control_pawn);
	auto result = world->OverlapMultiByChannel(overlap_results
											, control_pawn->GetActorLocation()
											, FQuat::Identity
											, ECollisionChannel::ECC_Pawn
											, FCollisionShape::MakeSphere(600.0f)
											, collision_query_params);

	if (result == true && overlap_results.IsEmpty() == false)
	{
		for (auto const& iter : overlap_results)
		{
			auto actor = iter.GetActor();
			if (actor->Tags.IsEmpty() == true)
				continue;

			OwnerComp.GetBlackboardComponent()->SetValueAsObject(ABase_AIController::target_key, actor);
			DrawDebugSphere(world, actor->GetActorLocation(), 600.0f, 10.0f, FColor::Blue, false, 0.2f);

			DrawDebugPoint(world, control_pawn->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
			DrawDebugLine(world, control_pawn->GetActorLocation(), actor->GetActorLocation(), FColor::Blue, false, 0.2f);

			OwnerComp.GetAIOwner()->MoveToActor(actor, 2.f);

			return;
		}
	}

	auto target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(ABase_AIController::target_key);
	if (target != nullptr)
	{
		OwnerComp.GetAIOwner()->MoveToActor(Cast<AActor>(target), 2.f);
	}

	DrawDebugSphere(world, control_pawn->GetActorLocation(), 600.0f, 16, FColor::Red, false, 0.2f);
}
