// Fill out your copyright notice in the Description page of Project Settings.


#include "Interact/Spawn/Spawning.h"
#include "Components/CapsuleComponent.h"
#include "Enemy/Enemy.h"
#include "GameFramework/CharacterMovementComponent.h"	

ASpawning::ASpawning()
	: range(FVector(10, 10, 10))
    , spawn_time(3.0f)
    , spawn_count(50)
    , current_count(0)
{
}

const bool ASpawning::Interact(AActor* _intereacting_actor) noexcept
{
	auto result = Super::Interact(_intereacting_actor);

    GetWorldTimerManager().SetTimer(spawn_timer, this, &ASpawning::Spawning, spawn_time, true);
    return result;
}

void ASpawning::Spawning() noexcept
{
    if (interacting_actor == nullptr)
    {
        GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, *FString("Intereacting Actor is null!!"));
        return;
    }

    if (current_count >= spawn_count)
    {
        GetWorldTimerManager().ClearTimer(spawn_timer);
        current_count = 0;
    }
    else
    {
        auto actor = spawning_actors_list[current_count];

        actor->PrimaryActorTick.bCanEverTick = true;
        actor->SetActorHiddenInGame(false);

        Cast<AEnemy>(actor)->SetGravity(true);
        Cast<AEnemy>(actor)->GetCapsuleComponent()->SetEnableGravity(true);
        actor->SetActorEnableCollision(true);

        Cast<ACharacter>(actor)->GetCharacterMovement()->GravityScale = 1;
        Cast<AEnemy>(actor)->SetSpawnType(ENEMY_SPAWN_TYPE::INTERACT);
        Cast<AEnemy>(actor)->SetTarget(interacting_actor);

        ++current_count;
    }
}

void ASpawning::BeginPlay()
{
	Super::BeginPlay();

	auto location = GetActorLocation();

	DrawDebugBox(GetWorld(), location, range, FColor::Purple, true);

    auto path = TEXT("/Game/WJ_Project/Character/Enemy/Zombie/BP_Zombie.BP_Zombie");

    for (int i = 0; i < spawn_count; ++i)
    {
        auto* cls = StaticLoadObject(UObject::StaticClass(), nullptr, path);
        UBlueprint* bp = Cast<UBlueprint>(cls);
        TSubclassOf<class UObject> blockBP = (UClass*)bp->GeneratedClass;

        FVector rand;
        rand.X = FMath::RandRange(-range.X, range.X);
        rand.Y = FMath::RandRange(-range.Y, range.Y);
        rand.Z = FMath::RandRange(-range.Z, range.Z);

        auto actor = GetWorld()->SpawnActor<AActor>(blockBP, GetActorLocation() + rand, GetActorRotation());
        Cast<APawn>(actor)->SpawnDefaultController();

        actor->PrimaryActorTick.bCanEverTick = false;
        actor->SetActorHiddenInGame(true);
        actor->SetActorEnableCollision(false);

        Cast<ACharacter>(actor)->GetCharacterMovement()->GravityScale = 0;
        Cast<AEnemy>(actor)->BeginPlay(ENEMY_SPAWN_TYPE::INTERACT);

        spawning_actors_list.Add(actor);
    }

}