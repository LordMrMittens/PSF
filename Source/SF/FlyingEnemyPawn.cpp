// Fill out your copyright notice in the Description page of Project Settings.

#include "FlyingEnemyPawn.h"
#include "GunComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "GameplayManager.h"
#include "PlayerPawn.h"

AFlyingEnemyPawn::AFlyingEnemyPawn()
{
    PrimaryActorTick.bCanEverTick = true;
}
void AFlyingEnemyPawn::BeginPlay()
{
    Super::BeginPlay();
    if(GameplayManager)
    PlayerActor = Cast<AActor>(GameplayManager->GetPlayerPawn());
    if (GunComponent)
    {
        GunComponent->OutOfAmmoDelegate.AddDynamic(this, &AFlyingEnemyPawn::LeaveLevel);
            GetWorldTimerManager().SetTimer(ShotTimerHandle, [this]()
    {
        if (GunComponent)
        {
            GunComponent->Aim(&UGunComponent::FireLasers);
        }
    }, ShotFrequency, true);
    }
    if(MainBodyComponent){
    		MainBodyComponent->OnComponentBeginOverlap.AddDynamic(this, &AFlyingEnemyPawn::OnOverlapStart);
	}

}

void AFlyingEnemyPawn::Move()
{
    
    FVector MoveDelta = MoveDirection * CurrentSpeed * GetWorld()->GetDeltaSeconds();
    if(!LeavingLevel){
    FVector CurrentLocation = GetActorLocation();
    LimitMovement(CurrentLocation, MoveDelta);
    CheckIfOutOfBounds(CurrentLocation, MoveDelta);
    }
    AddActorWorldOffset(MoveDelta, true);
    MoveDirection = OriginalMoveDirection;
    CurrentSpeed = Speed * CalculateTargetVelocity();
}

void AFlyingEnemyPawn::OnDeath()
{
    Super::OnDeath();
    GetWorldTimerManager().ClearAllTimersForObject(this); //this might cause timer issues
}

void AFlyingEnemyPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (bIsActive)
    {
        Steer();
    }
    
    
}

void AFlyingEnemyPawn::ResetPawn()
{
    Super::ResetPawn();
    LeavingLevel = false;
    PerformEvasiveManouevres = false;
    CanSteerTowardsPlayer = true;
    ResetEvasion();
}

void AFlyingEnemyPawn::Steer()
{
    if (LeavingLevel)
    {
        SteerOffLevel();
    }
    if (DetectObstacles() || PerformEvasiveManouevres)
    {
        Evade();
    }
    else if (CanSteerTowardsPlayer && ObstacleAvoidanceDirection == 0)
    {
        FVector PlayerLocation = GameplayManager->GetPlayerLocation();
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
    
    if (ObstacleAvoidanceDirection == 0)
    {
        CanSteerTowardsPlayer = false;
        int32 RandomDirection = FMath::RandRange(0, 1);
        ZObstacleAvoidanceStrength = FMath::RandRange(0.0f, 0.6f);
        ObstacleAvoidanceDirection = (RandomDirection == 0) ? -1 : 1;
    }
    ObstacleAvoidanceTimer += GetWorld()->GetDeltaSeconds();
    
    if (ObstacleAvoidanceTimer > ObstacleAvoidanceDuration)
    {
        ResetEvasion();
        return;
    }
    else
    {
        MoveDirection.Y = ObstacleAvoidanceDirection * SteerFactor * ObstacleAvoidanceStrength;
        MoveDirection.Z = 1 * SteerFactor * ObstacleAvoidanceStrength * ZObstacleAvoidanceStrength;
    }
    
}

void AFlyingEnemyPawn::ResetEvasion()
{
        ObstacleAvoidanceDirection = 0;
        ZObstacleAvoidanceStrength = 0;
        ObstacleAvoidanceTimer = 0;
        PerformEvasiveManouevres = false;
        CanSteerTowardsPlayer = true;
}

bool AFlyingEnemyPawn::DetectObstacles()
{
    FHitResult HitResult;
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(this);

    //change this to a sphere trace
    FVector TraceStart = GetActorLocation();
    FVector TraceEnd = TraceStart + MoveDirection * ObstacleAvoidanceDistance;
    bool bIsHit = GetWorld()->LineTraceSingleByChannel(HitResult,
                                                       TraceStart,
                                                       TraceEnd,
                                                       ECC_Visibility,
                                                       CollisionParams);

    return bIsHit;
}

void AFlyingEnemyPawn::LeaveLevel()
{
    GetWorldTimerManager().SetTimer(LeavingDelayTimerHandle, this, &AFlyingEnemyPawn::SteerOffLevel, HoldTimeBeforeLevelExit, false);
    GetWorldTimerManager().SetTimer(DeactivateTimerHandle, this, &AFlyingEnemyPawn::DeactivatePawn, TimeToDestroyWhenLeaving, false);
}

void AFlyingEnemyPawn::SteerOffLevel()
{
    LeavingLevel = true;
    CurrentSpeed = Speed * 0.25f;
    if (ObstacleAvoidanceDirection == 0)
    {
        int32 RandomDirection = FMath::RandRange(0, 1);
        ZObstacleAvoidanceStrength = FMath::RandRange(0.4f, 0.7f);
        ObstacleAvoidanceDirection = (RandomDirection == 0) ? -1 : 1;
    }
    MoveDirection.Y = ObstacleAvoidanceDirection * ZObstacleAvoidanceStrength;
    MoveDirection.Z = 1 * ZObstacleAvoidanceStrength;
    
}

void AFlyingEnemyPawn::OnOverlapStart(class UPrimitiveComponent *OverlappedComp, class AActor *OtherActor, class UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    if (OtherActor->GetOwner() != this)
    {
        PerformEvasiveManouevres = true;
    }
}
