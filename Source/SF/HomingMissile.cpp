// Fill out your copyright notice in the Description page of Project Settings.


#include "HomingMissile.h"
#include "GameplayManager.h"
#include "PlayerPawn.h"
#include "Kismet/GameplayStatics.h"
#include "HealthComponent.h"


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
    TargetDirection.X = Direction.X;
    TargetDirection.Z *=-1; 
    TargetDirection.Normalize();
    CurrentSpeed = Speed- ((HomingSpeed* .5f) * -1);
    
    
    Direction = FMath::VInterpConstantTo(Direction, TargetDirection, GetWorld()->GetDeltaSeconds(), HomingSpeed);
}

void AHomingMissile::OnDeath()
{
    Destroy();
}
