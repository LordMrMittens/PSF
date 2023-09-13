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

void UGunComponent::SetupGunComponent(AActor* Owner, float ShotSpeed, bool DoubleShot, USceneComponent* SingleLaserSource, TArray<USceneComponent*> MultiLasers){
	Speed = ShotSpeed;
	DoubleLaser = DoubleShot;
	SingleLaserSpawnPoint = SingleLaserSource;
	LaserSpawnPoints = MultiLasers;
	OwnerActor = Owner;
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
	struct FActorSpawnParameters params;
	params.Owner = OwnerActor;
	AProjectile *Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,
																  SpawnPoint->GetComponentLocation(),
																  this->GetComponentRotation(), 
																  params);
	if (Projectile!= nullptr)
	{
		Projectile->SetSpeed(Speed * ShotSpeedMultiplier);
	}

}
void UGunComponent::Aim(AActor* PlayerActor){
	    if (PlayerActor)
    {
        // Get the location of the player
        FVector PlayerLocation = PlayerActor->GetActorLocation();

        // Calculate the rotation to make the X-axis of the gun component aim at the player
        FVector GunDirection = PlayerLocation - GetOwner()->GetActorLocation();
        FRotator NewRotation = GunDirection.Rotation();
		

        // Optionally, you can limit the rotation to only affect the yaw (X-axis)
        // NewRotation.Pitch = 0.0f;
        // NewRotation.Roll = 0.0f;

        // Apply the new rotation to the gun component
	
        SetWorldRotation(NewRotation);
    }
}
