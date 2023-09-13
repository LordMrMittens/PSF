// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyingEnemyPawn.h"
#include "GunComponent.h"
#include "Kismet/GameplayStatics.h"


AFlyingEnemyPawn::AFlyingEnemyPawn()
{
    PrimaryActorTick.bCanEverTick = true;
    MainBodyComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainBody"));
    SetRootComponent(MainBodyComponent);
    
    SingleLaserSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("LaserSpawnPoint"));
    SingleLaserSpawnPoint->SetupAttachment(MainBodyComponent);

    DoubleLaserSpawnPointL = CreateDefaultSubobject<USceneComponent>(TEXT("LaserSpawnPointL"));
    DoubleLaserSpawnPointL->SetupAttachment(MainBodyComponent);
    LaserSpawnPoints.Add(DoubleLaserSpawnPointL);

    DoubleLaserSpawnPointR = CreateDefaultSubobject<USceneComponent>(TEXT("LaserSpawnPointR"));
    DoubleLaserSpawnPointR->SetupAttachment(MainBodyComponent);
    LaserSpawnPoints.Add(DoubleLaserSpawnPointR);

    GunComponent = CreateDefaultSubobject<UGunComponent>(TEXT("Gun"));
}
void AFlyingEnemyPawn::BeginPlay()
{
    Super::BeginPlay();
    PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    
     
}

void AFlyingEnemyPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    Steer();
}

void AFlyingEnemyPawn::Steer()
{
    float SteerFactor = 10; //times steering force in final script
    FVector PlayerLocation = PlayerActor->GetActorLocation();
    FVector EnemyLocation = GetActorLocation();
    FVector PlayerDirection = (PlayerLocation - EnemyLocation).GetSafeNormal();
    MoveDirection.Z = PlayerDirection.Z * SteerFactor;
    MoveDirection.Y = PlayerDirection.Y * SteerFactor;
}