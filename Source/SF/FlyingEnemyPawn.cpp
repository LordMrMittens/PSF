// Fill out your copyright notice in the Description page of Project Settings.

#include "FlyingEnemyPawn.h"
#include "GunComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

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
    GunComponent->SetupAttachment(MainBodyComponent);
}
void AFlyingEnemyPawn::BeginPlay()
{
    Super::BeginPlay();
    PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (GunComponent)
    {
        GunComponent->SetupGunComponent(this, Speed, AmmoAvailable, false, SingleLaserSpawnPoint, LaserSpawnPoints);
        GunComponent->OutOfAmmoDelegate.AddDynamic(this, &AFlyingEnemyPawn::LeaveLevel);
    }
    if(MainBodyComponent){
    		MainBodyComponent->OnComponentBeginOverlap.AddDynamic(this, &AFlyingEnemyPawn::OnOverlapStart);
	}
    GetWorldTimerManager().SetTimer(ShotTimerHandle, GunComponent, &UGunComponent::FireLasers, ShotFrequency, true);
}

void AFlyingEnemyPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    Steer();
    if (GunComponent != nullptr)
    {
        GunComponent->Aim(PlayerActor);
    }
}

void AFlyingEnemyPawn::Steer()
{
    if (LeavingLevel)
    {
        LeaveLevel();
    }
    if (DetectObstacles()||PerformEvasiveManouevres)
    {
        Evade();
    }
    else if (CanSteerTowardsPlayer && ObstacleAvoidanceDirection == 0)
    {
        FVector PlayerLocation = PlayerActor->GetActorLocation();
        FVector EnemyLocation = GetActorLocation();
        FVector PlayerDirection = (PlayerLocation - EnemyLocation).GetSafeNormal();
        if (EnemyLocation.Z > VerticalDistanceToPlayerOffset || EnemyLocation.Z < VerticalDistanceToPlayerOffset)
        {
            MoveDirection.Z = PlayerDirection.Z * SteerFactor;
        }
        if (EnemyLocation.Y > HorizontalDistanceToPlayerOffset || EnemyLocation.Y < HorizontalDistanceToPlayerOffset)
        {
            MoveDirection.Y = PlayerDirection.Y * SteerFactor;
        }
    }
}

void AFlyingEnemyPawn::Evade()
{
    ObstacleAvoidanceTimer += GetWorld()->GetDeltaSeconds();
    CanSteerTowardsPlayer = false;
    if (ObstacleAvoidanceDirection == 0)
    {
        int32 RandomDirection = FMath::RandRange(0, 1);
        ZObstacleAvoidanceStrength = FMath::RandRange(0.0f, 0.6f);
        ObstacleAvoidanceDirection = (RandomDirection == 0) ? -1 : 1;
    }
    if (ObstacleAvoidanceTimer > ObstacleAvoidanceDuration)
    {
        ObstacleAvoidanceDirection = 0;
        ZObstacleAvoidanceStrength = 0;
        PerformEvasiveManouevres = false;
    }
    MoveDirection.Y = ObstacleAvoidanceDirection * SteerFactor * ObstacleAvoidanceStrength;
    MoveDirection.Z = 1 * SteerFactor * ObstacleAvoidanceStrength * ZObstacleAvoidanceStrength;
    if (ObstacleAvoidanceTimer > ResetSteeringDuration)
    {
        ObstacleAvoidanceTimer = 0;
        CanSteerTowardsPlayer = true;
    }
}

bool AFlyingEnemyPawn::DetectObstacles()
{
    FHitResult HitResult;
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(this);
    FVector TraceStart = GetActorLocation();
    FVector TraceEnd = TraceStart + MoveDirection * ObstacleAvoidanceDistance;
    DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1);
    bool bIsHit = GetWorld()->LineTraceSingleByChannel(HitResult,
                                                       TraceStart,
                                                       TraceEnd,
                                                       ECC_Visibility,
                                                       CollisionParams);

    return bIsHit;
}

void AFlyingEnemyPawn::LeaveLevel()
{
    LeavingLevel = true;
    if (ObstacleAvoidanceDirection == 0)
    {
        int32 RandomDirection = FMath::RandRange(0, 1);
        ZObstacleAvoidanceStrength = FMath::RandRange(0.0f, 0.6f);
        ObstacleAvoidanceDirection = (RandomDirection == 0) ? -1 : 1;
    }
    MoveDirection.Y = ObstacleAvoidanceDirection * ZObstacleAvoidanceStrength;
    MoveDirection.Z = 1 * ZObstacleAvoidanceStrength;
}

void AFlyingEnemyPawn::OnOverlapStart(class UPrimitiveComponent *OverlappedComp, class AActor *OtherActor, class UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    if(OtherActor->GetOwner()!=this){
    PerformEvasiveManouevres = true;}
}
