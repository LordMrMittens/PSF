// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomb.h"
#include "HealthComponent.h"

ABomb::ABomb()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ABomb::BeginPlay()
{
    Super::BeginPlay();
    StartingPosition = GetActorLocation();
}
void ABomb::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    float Distance = FVector::Distance(StartingPosition, GetActorLocation());
    if(Distance>DistanceToExplode){
        Explode();
    }
}

void ABomb::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
}

void ABomb::OnOverlapStart(class UPrimitiveComponent *OverlappedComp, class AActor *OtherActor, class UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    if (OtherActor != Owner)
    {
        
            UHealthComponent* HealthComponent = OtherActor->FindComponentByClass<UHealthComponent>();
        if (HealthComponent)
        {
            HealthComponent->TakeDamage(BaseDamage);
        }
        Explode();
    }
}

void ABomb::Explode()
{
TArray<FHitResult> HitResults;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);
    bool bHit = GetWorld()->SweepMultiByObjectType(HitResults, GetActorLocation(), GetActorLocation(), FQuat::Identity, FCollisionObjectQueryParams::AllObjects, FCollisionShape::MakeSphere(ExplosionRadius), Params);
    for (const FHitResult& HitResult : HitResults)
    {
        AActor* HitActor = HitResult.GetActor();
        if(HitActor != nullptr && HitActor != this && HitActor != Owner)
        {
            UHealthComponent* HealthComponent = HitActor->FindComponentByClass<UHealthComponent>();
            if (HealthComponent)
            {
                HealthComponent->TakeDamage(BaseDamage);
            }
        }
    Destroy();
}
}
