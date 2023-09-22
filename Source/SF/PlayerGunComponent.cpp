// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerGunComponent.h"
#include "Projectile.h"

void UPlayerGunComponent::BeginPlay()
{
    Super::BeginPlay();
    
}

void UPlayerGunComponent::SetupGunComponent(FGunComponentConfig *GunConfig, AActor *_OwnerActor)
{
	Super::SetupGunComponent(GunConfig, _OwnerActor);
	ActiveProjectileClass = ProjectileClass;
	ResetLasers();
}

void UPlayerGunComponent::EnhanceLasers()
{
	if (DoubleLaser)
	{
		PowerLaser = true;
        ActiveProjectileClass = SecondaryProjectileClass;
	}
	else
	{
		DoubleLaser = true;
	}
}

void UPlayerGunComponent::ResetLasers()
{
    PowerLaser = false;
    DoubleLaser = false;
    ActiveProjectileClass = ProjectileClass;
}

void UPlayerGunComponent::SpawnLaser(USceneComponent *SpawnPoint)
{
    struct FActorSpawnParameters params;
	params.Owner = OwnerActor;
	AProjectile *Projectile = GetWorld()->SpawnActor<AProjectile>(ActiveProjectileClass,
																  SpawnPoint->GetComponentLocation(),
																  this->GetComponentRotation(),
																  params);
	if (Projectile != nullptr)
	{
		Projectile->SetSpeed(Speed * ShotSpeedMultiplier);
	}
}


