// Fill out your copyright notice in the Description page of Project Settings.


#include "Explosion_Damaging.h"
#include "Components/SphereComponent.h"
#include "HealthComponent.h"


AExplosion_Damaging::AExplosion_Damaging()
{
    
	SphereComponent->SetSphereRadius(StartSize);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AExplosion_Damaging::OnOverlapBegin);
}

void AExplosion_Damaging::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!DamagedActors.Contains(OtherActor))
    {
        UHealthComponent* HealthComponent = OtherActor->FindComponentByClass<UHealthComponent>();
        if (HealthComponent)
        {
            HealthComponent->TakeDamage(BaseDamage);
        }
        DamagedActors.Add(OtherActor);
    }
}
