// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"
#include "SpawnerComponent.h"


AEnemyPawn::AEnemyPawn()
{
    SpawnerComponent = CreateDefaultSubobject<USpawnerComponent>(TEXT("SpawnerComponent"));
}

void AEnemyPawn::OnDeath()
{
    SpawnerComponent->SpawnObject(GetActorLocation(), GetActorRotation());
    Super::OnDeath();
}

