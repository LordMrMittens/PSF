// Fill out your copyright notice in the Description page of Project Settings.


#include "LandEnemyPawn.h"
#include "GunComponent.h"
#include "Components/CapsuleComponent.h"


ALandEnemyPawn::ALandEnemyPawn()
{
    PrimaryActorTick.bCanEverTick = true;
    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Comp"));
    SetRootComponent(CapsuleComponent);
    MainBodyComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainBody"));
    MainBodyComponent->SetupAttachment(CapsuleComponent);
    GunComponent = CreateDefaultSubobject<UGunComponent>(TEXT("Gun"));
    GunComponent->SetupAttachment(MainBodyComponent);
    TurretMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
    TurretMeshComponent->SetupAttachment(GunComponent);
    SingleLaserSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("LaserSpawnPoint"));
    SingleLaserSpawnPoint->SetupAttachment(TurretMeshComponent);
    DoubleLaserSpawnPointL = CreateDefaultSubobject<USceneComponent>(TEXT("LaserSpawnPointL"));
    DoubleLaserSpawnPointL->SetupAttachment(TurretMeshComponent);
    LaserSpawnPoints.Add(DoubleLaserSpawnPointL);
    DoubleLaserSpawnPointR = CreateDefaultSubobject<USceneComponent>(TEXT("LaserSpawnPointR"));
    DoubleLaserSpawnPointR->SetupAttachment(TurretMeshComponent);
    LaserSpawnPoints.Add(DoubleLaserSpawnPointR);
    
}

void ALandEnemyPawn::BeginPlay()
{
    Super::BeginPlay();
    if(GunComponent!=nullptr){
        GunComponent->SetupGunComponent(this, Speed, -1, false, SingleLaserSpawnPoint, LaserSpawnPoints);
    }
}
void ALandEnemyPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ALandEnemyPawn::Move()
{
    
}

void ALandEnemyPawn::SetRotation()
{
    if(MovementNodes.Num()>0){
        
    }
}


