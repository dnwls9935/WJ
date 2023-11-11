// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/AI/Controller/BTService_Detect.h"
#include "Enemy/AI/Controller/Base_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BaseCharacter/BaseCharacter.h"
#include "Enemy/Enemy.h"


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

	if (control_pawn->PrimaryActorTick.bCanEverTick == false)
		return;

	auto cast_pawn = Cast<ABaseCharacter>(control_pawn);
	if (cast_pawn->GetDead() == true)
		return;

	auto world = control_pawn->GetWorld();
	if (world == nullptr)
		return;

	switch (cast_pawn->GetActorType())
	{
	case ACTOR_TYPE::ENEMY:
	{
		auto enemy_cast_pawn = Cast<AEnemy>(cast_pawn);
		if (enemy_cast_pawn->GetIsIntro() == true)
			return;

		auto target = enemy_cast_pawn->GetTarget();
		if (target == nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("Target Actor is null!! :: %s"), *cast_pawn->GetName()));
			return;
		}

		OwnerComp.GetBlackboardComponent()->SetValueAsObject(ABase_AIController::target_key, target);
		UAIBlueprintHelperLibrary::SimpleMoveToActor(OwnerComp.GetAIOwner(), target);
		break;
	}
	default:
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("Actor Type is not Selected :: %s"), *cast_pawn->GetName()));
		return;
	}


	///* 감지된 엑터들 */
	//TArray<FOverlapResult> overlap_results;
	//FCollisionQueryParams collision_query_params(NAME_None, false, control_pawn);
	//auto result = world->OverlapMultiByChannel(overlap_results
	//										, control_pawn->GetActorLocation()
	//										, FQuat::Identity
	//										, ECollisionChannel::ECC_Pawn
	//										, FCollisionShape::MakeSphere(3000.0f)
	//										, collision_query_params);

	//if (result == true && overlap_results.IsEmpty() == false)
	//{
	//	for (auto const& iter : overlap_results)
	//	{
	//		auto actor = iter.GetActor();
	//		if (actor->Tags.IsEmpty() == true)
	//			continue;

	//		OwnerComp.GetBlackboardComponent()->SetValueAsObject(ABase_AIController::target_key, actor);
	//		DrawDebugSphere(world, actor->GetActorLocation(), 3000.0f, 10.0f, FColor::Blue, false, 0.2f);

	//		DrawDebugPoint(world, control_pawn->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
	//		DrawDebugLine(world, control_pawn->GetActorLocation(), actor->GetActorLocation(), FColor::Blue, false, 0.2f);

	//		UAIBlueprintHelperLibrary::SimpleMoveToActor(OwnerComp.GetAIOwner(), actor);

	//		//OwnerComp.GetAIOwner()->MoveToActor(actor, 2.f);

	//		return;
	//	}
	//}

	//auto target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(ABase_AIController::target_key);
	//if (target != nullptr)
	//{
	//	//OwnerComp.GetAIOwner()->MoveToActor(Cast<AActor>(target), 2.f);
	//	//OwnerComp.GetAIOwner()->GetPawn()->bUseControllerRotationYaw = true;
	//}

	//DrawDebugSphere(world, control_pawn->GetActorLocation(), 3000.0f, 16, FColor::Red, false, 0.2f);
}
