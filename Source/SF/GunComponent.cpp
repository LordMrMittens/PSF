// Fill out your copyright notice in the Description page of Project Settings.

#include "GunComponent.h"
#include "Projectile.h"
#include "PlayerPawn.h"
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
void UGunComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGunComponent::SetupGunComponent(AActor *Owner, float ShotSpeed, int32 AmmoAvailable ,bool DoubleShot, USceneComponent *SingleLaserSource, TArray<USceneComponent *> MultiLasers)
{
	Speed = ShotSpeed;
	DoubleLaser = DoubleShot;
	SingleLaserSpawnPoint = SingleLaserSource;
	LaserSpawnPoints = MultiLasers;
	OwnerActor = Owner;
	AvailableAmmo = AmmoAvailable;
}

void UGunComponent::FireLasers()
{
	if (AvailableAmmo != 0)
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
		if (AvailableAmmo > 0)
		{
			AvailableAmmo--;
			if( AvailableAmmo==0){
				OutOfAmmoDelegate.Broadcast();
			}
		}
	}
}
void UGunComponent::SpawnLaser(USceneComponent *SpawnPoint)
{
	struct FActorSpawnParameters params;
	params.Owner = OwnerActor;
	AProjectile *Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,
																  SpawnPoint->GetComponentLocation(),
																  this->GetComponentRotation(),
																  params);
	if (Projectile != nullptr)
	{
		Projectile->SetSpeed(Speed * ShotSpeedMultiplier);
	}
}
void UGunComponent::Aim(AActor *PlayerActor)
{
	if (PlayerActor)
	{

	        FVector PlayerLocation = PlayerActor->GetActorLocation();
        FVector PlayerVelocity = FVector::ZeroVector;


        APlayerPawn* PlayerPawn = Cast<APlayerPawn>(PlayerActor);
        if (PlayerPawn)
        {
            PlayerVelocity = PlayerPawn->CalculateVelocity();
        }

        float TimeToHit = FVector::Dist(GetComponentLocation(), PlayerLocation) / (Speed * ShotSpeedMultiplier*ShotLeadMultiplier);
        
        FVector PredictedPlayerLocation = PlayerLocation + (PlayerVelocity * TimeToHit);
        FVector GunDirection = PredictedPlayerLocation - GetComponentLocation();
        FRotator NewRotation = GunDirection.Rotation();

        SetRelativeRotation(NewRotation);
	}
}
