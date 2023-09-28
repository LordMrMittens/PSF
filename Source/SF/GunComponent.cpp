// Fill out your copyright notice in the Description page of Project Settings.

#include "GunComponent.h"
#include "Projectile.h"
#include "PlayerPawn.h"
#include "Bomb.h"
#include "GameplayManager.h"
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
	GameplayManager = Cast<AGameplayManager>(UGameplayStatics::GetActorOfClass(GetWorld(),AGameplayManager::StaticClass()));
	if(GameplayManager==nullptr){
		UE_LOG(LogTemp, Error, TEXT("GameplayManager is null"));
	}
	// ...
}

// Called every frame
void UGunComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGunComponent::SetupGunComponent(FGunComponentConfig* GunConfig)
{
	ShotSpeedMultiplier = GunConfig->_ShotSpeedMultiplier;
	ShotLeadErrorMin = GunConfig->_ShotLeadErrorMin;
	ShotLeadErrorMax = GunConfig->_ShotLeadErrorMax;
	ProjectileClass = GunConfig->_ProjectileClass;
	SecondaryProjectileClass = GunConfig->_SecondaryProjectileClass;
	BombClass = GunConfig->_BombClass;
	AvailableAmmo = GunConfig->_AvailableAmmo;
	AvailableBombs= GunConfig->_AvailableBombs;
	bUsesWorldRotationWhenAiming = GunConfig->_bUsesWorldRotationWhenAiming;
	Speed = GunConfig->_Speed;
	DoubleLaser = GunConfig->_DoubleLaser;
	SingleLaserSpawnPoint = GunConfig->_SingleLaserSpawnPoint;
	LaserSpawnPoints = GunConfig->_LaserSpawnPoints;
	OwnerActor = GetOwner();
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
			if (AvailableAmmo == 0)
			{
				OutOfAmmoDelegate.Broadcast();
			}
		}
	}
}
void UGunComponent::FireBombs()
{
	if (AvailableBombs != 0)
	{
		SpawnBombs(SingleLaserSpawnPoint);
		if (AvailableBombs > 0)
		{
			AvailableBombs--;
		}
	}
}
void UGunComponent::SpawnBombs(USceneComponent *SpawnPoint)
{
	if(BombClass==nullptr){
		UE_LOG(LogTemp, Error, TEXT("BombClass is null"));
		return;
	}
	if(SpawnPoint==nullptr){
		UE_LOG(LogTemp, Error, TEXT("SpawnPoint is null"));
		return;
	}
	struct FActorSpawnParameters params;
	params.Owner = OwnerActor;
	AProjectile *Bomb = GetWorld()->SpawnActor<AProjectile>(BombClass,
												SpawnPoint->GetComponentLocation(),
												this->GetComponentRotation(),
												params);
	if (Bomb != nullptr)
	{
		Bomb->SetSpeed(Speed * ShotSpeedMultiplier);
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
void UGunComponent::Aim(void (UGunComponent::*FireFunctionPtr)())
{
	if (GameplayManager)
	{
		float LeadFactor = 1.0f;
		FVector PlayerLocation = GameplayManager->GetPlayerLocation();
		FVector PlayerVelocity = FVector::ZeroVector;

		APlayerPawn *PlayerPawn = GameplayManager->GetPlayerPawn();
		if (PlayerPawn)
		{
			PlayerVelocity = PlayerPawn->GetVelocity();
		}
		FVector RelativePlayerLocation = PlayerLocation - GetComponentLocation();
		float TimeToHit = RelativePlayerLocation.Size() / (Speed * ShotSpeedMultiplier);
		LeadFactor = FMath::RandRange(ShotLeadErrorMin, ShotLeadErrorMax);
		FVector PredictedPlayerLocation = PlayerLocation + (PlayerVelocity * (TimeToHit * LeadFactor));

		FVector GunDirection = PredictedPlayerLocation - GetComponentLocation();
		FRotator NewRotation = GunDirection.Rotation();
		if (bUsesWorldRotationWhenAiming)
		{
			SetWorldRotation(NewRotation);
		}
		else
		{
			SetRelativeRotation(NewRotation);
		}
		(this->*FireFunctionPtr)();
	} else {
		UE_LOG(LogTemp, Error, TEXT("GameplayManager is null"));
	}
}
void UGunComponent::AddBomb(int32 BombsToAdd){
	BombsToAdd += AvailableBombs;
}
