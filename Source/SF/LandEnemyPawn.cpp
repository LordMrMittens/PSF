// Fill out your copyright notice in the Description page of Project Settings.


#include "LandEnemyPawn.h"
#include "GunComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameplayManager.h"
#include "PlayerPawn.h"


ALandEnemyPawn::ALandEnemyPawn()
{
    PrimaryActorTick.bCanEverTick = true;
    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Comp"));
    SetRootComponent(CapsuleComponent);
    MainBodyComponent->SetupAttachment(CapsuleComponent);
    GunComponent->SetupAttachment(MainBodyComponent);
    TurretMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
    TurretMeshComponent->SetupAttachment(GunComponent);
    SingleLaserSpawnPoint->SetupAttachment(TurretMeshComponent);
    DoubleLaserSpawnPointL->SetupAttachment(TurretMeshComponent);
    LaserSpawnPoints.Add(DoubleLaserSpawnPointL);
    DoubleLaserSpawnPointR->SetupAttachment(TurretMeshComponent);
    LaserSpawnPoints.Add(DoubleLaserSpawnPointR);
}

void ALandEnemyPawn::BeginPlay()
{
    Super::BeginPlay();
    if (GunComponent != nullptr)
    {
        GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ALandEnemyPawn::AimAndShoot, ShotFrequency, true);
    }
    CurrentTargetIndex = 0;
    PlayerActor = Cast<AActor>(GameplayManager->GetPlayerPawn());
}
void ALandEnemyPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (bStayInPosition == false)
    {
        Move();
    }
}

AActor *ALandEnemyPawn::SetTarget()
{
    if (MovementNodes.Num() > 0)
    {
        if (CurrentTargetIndex >= MovementNodes.Num())
        {
            if (bLoopsPositions)
            {
                bReturning = true;
                CurrentTargetIndex = MovementNodes.Num() -1;
                return MovementNodes[CurrentTargetIndex];
            }
            else
            {
                bStayInPosition = true;
                return nullptr;
                
            }
        }
        if (CurrentTargetIndex < 0)
        {
            bReturning = false;
            CurrentTargetIndex = 0;
            return MovementNodes[CurrentTargetIndex];
        }
        return MovementNodes[CurrentTargetIndex];
    } else{
        bStayInPosition = true;
        return nullptr;
    }
}

void ALandEnemyPawn::Move()
{
    if (CurrentTarget == nullptr)
    {
        CurrentTarget = SetTarget();
    }
    if (CurrentTarget != nullptr && IsPlayerInRange() &&RotationSet())
    {
        FVector ForwardVector = GetActorForwardVector();
        FVector NewLocation = GetActorLocation() + (ForwardVector * MovementSpeed * GetWorld()->GetDeltaSeconds());
        SetActorLocation(NewLocation);
        float DistanceToTarget = FVector::Dist(GetActorLocation(), CurrentTarget->GetActorLocation());
        if (DistanceToTarget < MinimumDistanceToTarget)
        {
            CurrentTarget = nullptr;
            if (MovementNodes.Num() > 1)
            {
                if (bReturning)
                {
                    CurrentTargetIndex--;
                }
                else
                {
                    CurrentTargetIndex++;
                }
            }
            else
            {
                bStayInPosition = true;
            }
        }
    }
}

bool ALandEnemyPawn::RotationSet()
{
    FVector DirectionToTarget = (CurrentTarget->GetActorLocation() - GetActorLocation()).GetSafeNormal();
    FRotator TargetRotation = FRotationMatrix::MakeFromX(DirectionToTarget).Rotator();

        // Gradually interpolate the actor's rotation towards the target
    FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, GetWorld()->GetDeltaSeconds(), RotationInterpolationSpeed);
    SetActorRotation(NewRotation);
    bool bIsFacingTarget = FVector::DotProduct(GetActorForwardVector(), DirectionToTarget) >= 0.9f; // Adjust the threshold as needed

    return bIsFacingTarget;
}

bool ALandEnemyPawn::IsPlayerInRange() const
{
    float Distance = FVector::Dist(GetActorLocation(), GameplayManager->GetPlayerLocation());
    return Distance < ActiveDistance;
}

void ALandEnemyPawn::AimAndShoot()
{
    if (IsPlayerInRange())
    {
        GunComponent->Aim(&UGunComponent::FireLasers);
    }
    
    
}


