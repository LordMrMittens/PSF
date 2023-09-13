// Fill out your copyright notice in the Description page of Project Settings.


#include "GunComponent.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UGunComponent::UGunComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGunComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGunComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGunComponent::SetupGunComponent(float ShotSpeed, bool DoubleShot, USceneComponent* SingleLaserSource, TArray<USceneComponent*> MultiLasers){
	Speed = ShotSpeed;
	DoubleLaser = DoubleShot;
	SingleLaserSpawnPoint = SingleLaserSource;
	LaserSpawnPoints = MultiLasers;
}

void UGunComponent::FireLasers()
{
	if (DoubleLaser)
	{
		for (USceneComponent *SpawnPoint : LaserSpawnPoints)
		{
			SpawnLaser(SpawnPoint);
		}
	}
	else
	{
		SpawnLaser(SingleLaserSpawnPoint);
	}
}
void UGunComponent::SpawnLaser(USceneComponent *SpawnPoint)
{
	    AProjectile *Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,
                                                                  SpawnPoint->GetComponentLocation(),
                                                                  SpawnPoint->GetComponentRotation());
    if (Projectile)
    {
		
        Projectile->SetOwner(GetOwner());
        Projectile->SetSpeed(Speed * 4);
    }
}
