// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomb.h"


void ABomb::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    
}

void ABomb::OnOverlapStart(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
   Explode();
}

void ABomb::Explode()
{
     UE_LOG(LogTemp, Error, TEXT("Bomb Exploded"));
     Destroy();
}

void ABomb::BeginPlay()
{
    
    Super::BeginPlay();
}
