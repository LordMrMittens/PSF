// Fill out your copyright notice in the Description page of Project Settings.


#include "BombEnemyFlak.h"
#include "GameplayManager.h"
#include "Kismet/GameplayStatics.h"

ABombEnemyFlak::ABombEnemyFlak()
{
    
}

    


void ABombEnemyFlak::BeginPlay()
{
    Super::BeginPlay();
    GameplayManager = Cast<AGameplayManager>(UGameplayStatics::GetActorOfClass(GetWorld(),AGameplayManager::StaticClass()));
}

void ABombEnemyFlak::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    float DistanceToPlayer = CalculateYZDistanceToPlayer();
    float XDistanceToPlayer = CalculateXDistanceToPlayer();
    if(DistanceToPlayer > PreviousDistanceToPlayer || DistanceToPlayer < MinDistanceToExplode)
    {
        bYZDistanceMet = true;
    }
    if (bYZDistanceMet && XDistanceToPlayer < MinXDistanceToExplode * 1.5f)
    {
        Explode();
    }
    if (XDistanceToPlayer < MinXDistanceToExplode)
    {
        Explode();
    }
    PreviousDistanceToPlayer = DistanceToPlayer;
}

float ABombEnemyFlak::CalculateYZDistanceToPlayer()
{
    if(GameplayManager != nullptr)
    {
        FVector MyYZLocation = FVector(GetActorLocation().X, 0, 0);
        FVector PlayerYZLocation = FVector(GameplayManager->GetPlayerLocation().X, 0, 0);
        return FVector::Dist(MyYZLocation, PlayerYZLocation);
    }
    else
    {
        UE_LOG(LogTemp, Display, TEXT("GameplayManager is null"));
        return 0;
    }
}

float ABombEnemyFlak::CalculateXDistanceToPlayer()
{
    FVector MyXLocation = FVector(0, GetActorLocation().Y, GetActorLocation().Z);
    FVector PlayerXLocation = FVector(0, GameplayManager->GetPlayerLocation().Y, GameplayManager->GetPlayerLocation().Z);
    return FVector::Dist(MyXLocation, PlayerXLocation);
}