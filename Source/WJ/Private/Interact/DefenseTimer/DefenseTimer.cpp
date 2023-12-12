// Fill out your copyright notice in the Description page of Project Settings.


#include "Interact/DefenseTimer/DefenseTimer.h"
#include "Enemy/Enemy.h"
#include "GameFramework/CharacterMovementComponent.h"	
#include "Components/CapsuleComponent.h"

ADefenseTimer::ADefenseTimer()
	: range(FVector(10, 10, 10))
	, spawn_time(2.f)
    , defense_time(60.f)
    , is_defense_begin(false)
{
    interact_type = INTERACT_TYPE::NONE;
}


const bool ADefenseTimer::Interact(AActor* _intereacting_actor) noexcept
{
    auto result = Super::Interact(_intereacting_actor);
    if (result == false)
        return false;

    if (is_defense_begin == true)
        return false;

    is_defense_begin = true;
    GetWorldTimerManager().SetTimer(defense_timer, defense_time, false);
    GetWorldTimerManager().SetTimer(spawn_timer, this, &ADefenseTimer::Spawning, spawn_time, true);
    return result;
}

void ADefenseTimer::Tick(float _deltaTime)
{
    Super::Tick(_deltaTime);

    if (is_defense_begin == false)
        return;

    auto timer = GetWorldTimerManager().GetTimerElapsed(defense_timer);
    if (timer <= -1 || timer >= defense_time)
    {
        GetWorldTimerManager().ClearTimer(defense_timer);
        GetWorldTimerManager().ClearTimer(spawn_timer);
    }
}

void ADefenseTimer::Spawning() noexcept
{
    auto location = GetActorLocation();

    DrawDebugBox(GetWorld(), location, range, FColor::Purple, true);

    auto path = TEXT("/Game/WJ_Project/Character/Enemy/Zombie/BP_Zombie.BP_Zombie");
    auto* cls = StaticLoadObject(UObject::StaticClass(), nullptr, path);
    UBlueprint* bp = Cast<UBlueprint>(cls);
    TSubclassOf<class UObject> blockBP = (UClass*)bp->GeneratedClass;

    FVector rand;
    rand.X = FMath::RandRange(-range.X, range.X);
    rand.Y = FMath::RandRange(-range.Y, range.Y);
    rand.Z = FMath::RandRange(-range.Z, range.Z);

    auto actor = GetWorld()->SpawnActor<AActor>(blockBP, GetActorLocation() + rand, GetActorRotation());
    if (actor == nullptr)
        return;

    actor->PrimaryActorTick.bCanEverTick = true;
    actor->SetActorHiddenInGame(false);

    Cast<AEnemy>(actor)->SetGravity(true);
    Cast<AEnemy>(actor)->GetCapsuleComponent()->SetEnableGravity(true);
    actor->SetActorEnableCollision(true);


    Cast<APawn>(actor)->SpawnDefaultController();
    Cast<AEnemy>(actor)->BeginPlay(ENEMY_SPAWN_TYPE::DEFENSE);

    Cast<AEnemy>(actor)->SetSpawnType(ENEMY_SPAWN_TYPE::DEFENSE);
    Cast<AEnemy>(actor)->SetTarget(interacting_actor);


    in_game_mode->AddDefenseActor(actor);
}

void ADefenseTimer::BeginPlay()
{
    Super::BeginPlay();

    auto location = GetActorLocation();

    DrawDebugBox(GetWorld(), location, range, FColor::Purple, true);

}
