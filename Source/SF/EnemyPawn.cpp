// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"
#include "SpawnerComponent.h"
#include "GameplayManager.h"


AEnemyPawn::AEnemyPawn()
{
    SpawnerComponent = CreateDefaultSubobject<USpawnerComponent>(TEXT("SpawnerComponent"));
}

void AEnemyPawn::OnDeath()
{
    SpawnerComponent->SpawnObject(GetActorLocation(), GetActorRotation());
    GunComponent->bIsAlive = false;
    Super::OnDeath();
}

float AEnemyPawn::CalculateTargetVelocity()
{
    float SpeedModifier = 1;
    if (GameplayManager)
    {
        FVector PlayerLocation = GameplayManager->GetPlayerLocation();
        FVector PlayerLocationWithOffset = FVector(PlayerLocation.X,0, 0);
        FVector CurrentLocationWithOffset = FVector(GetActorLocation().X,0, 0);
        float DistanceToPlayer = FVector::Dist(CurrentLocationWithOffset, PlayerLocationWithOffset);
        if (DistanceToPlayer > MaxTargetDistanceFromPlayer)
        {
            SpeedModifier = .3f;
        }
        else if (DistanceToPlayer < MinTargetDistanceFromPlayer)
        {
            SpeedModifier = 2.5f;
        }
    }
    return SpeedModifier;
}
