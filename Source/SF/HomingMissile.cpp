// Fill out your copyright notice in the Description page of Project Settings.


#include "HomingMissile.h"
#include "GameplayManager.h"
#include "PlayerPawn.h"
#include "Kismet/GameplayStatics.h"
#include "HealthComponent.h"
#include "Engine/World.h"



AHomingMissile::AHomingMissile()
{
    HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

void AHomingMissile::BeginPlay()
{
    Super::BeginPlay();
    GameplayManager = Cast<AGameplayManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AGameplayManager::StaticClass()));
    Speed *= -1;
    CurrentSpeed = Speed;
        if(HealthComponent != nullptr){
        HealthComponent->SetUpHealthComponent(&HealthConfiguration);
        HealthComponent->OnOutOfHealth.AddDynamic(this, &AHomingMissile::OnDeath);
        
    }
}

void AHomingMissile::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if(GameplayManager){
    SteerTowards(GameplayManager->GetPlayerPawn());}
}

void AHomingMissile::SteerTowards(AActor* TargetActor)
{
    if (!GameplayManager)
    {
        UE_LOG(LogTemp, Error, TEXT("GameplayManager is null"));
        return;
    }
    FVector TargetLocation = TargetActor->GetActorLocation();
    FVector MissileLocation = GetActorLocation();
    FVector TargetDirection = (TargetLocation - MissileLocation).GetSafeNormal();

    FRotator TargetRotation = TargetDirection.Rotation();
    float DistanceToTargetonX = FMath::Abs(TargetLocation.X - MissileLocation.X);
    DistanceToTargetonX < MinTrackingDistance ? bIsHoming = false : bIsHoming = true;
    bIsHoming ? SetActorRotation(TargetRotation* TurningMultiplier ) : SetActorRotation(GetActorRotation());

    CurrentSpeed = Speed + SlowdownOffset;
}

void AHomingMissile::OnDeath()
{
    Destroy();
}
