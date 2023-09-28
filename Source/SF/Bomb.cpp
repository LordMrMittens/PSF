// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomb.h"
#include "HealthComponent.h"
#include "Explosion_Damaging.h"
#include "Kismet/GameplayStatics.h"

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
        if(bIsExploding == false){
        Explode();}
    }
}

void ABomb::Explode()
{
    if(bIsExploding){
        return;
    }
    bIsExploding = true;
    if (DamagingExplosionClass == nullptr)
    {
        UE_LOG(LogTemp, Display, TEXT("Damaging exploson class is null"));
        return;
    }
    
    AExplosion_Damaging* Explosion = GetWorld()->SpawnActor<AExplosion_Damaging>(DamagingExplosionClass,GetActorLocation(),GetActorRotation());
    Explosion->SetMaxSize(ExplosionRadius); 
    Destroy();
}
