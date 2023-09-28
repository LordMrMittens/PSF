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
    if(GameplayManager)
{   
    float XDistanceToPlayer = CalculateXDistanceToPlayer();
    if (XDistanceToPlayer < MinXDistanceToExplode && bIsExploding == false || XDistanceToPlayer > PreviousXDistanceToPlayer && bIsExploding == false)
    {
        Explode();
    }
    PreviousXDistanceToPlayer = XDistanceToPlayer;}
    //SteerTowards();
}

float ABombEnemyFlak::CalculateXDistanceToPlayer()
{
    FVector MyXLocation = FVector( GetActorLocation().X, 0,0);
    FVector PlayerXLocation = FVector(GameplayManager->GetPlayerLocation().X,0,0);
    return FVector::Dist(MyXLocation, PlayerXLocation);
}