// Fill out your copyright notice in the Description page of Project Settings.


#include "LandEnemyPawn.h"
#include "GunComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"


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
    if (GunComponent != nullptr)
    {
        GunComponent->SetupGunComponent(this, 100, -1, false, SingleLaserSpawnPoint, LaserSpawnPoints);
        GetWorldTimerManager().SetTimer(ShotTimerHandle, GunComponent, &UGunComponent::FireLasers, ShotFrequency, true);
    }
    CurrentTargetIndex = 0;
    PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
}
void ALandEnemyPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (bStayInPosition == false)
    {
        Move();
    }
    if(GunComponent && PlayerActor){
        GunComponent->Aim(PlayerActor);
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
                UE_LOG(LogTemp, Display, TEXT("cycling"));
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
            UE_LOG(LogTemp, Display, TEXT("cycling back"));
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
    if (CurrentTarget != nullptr && RotationSet())
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


