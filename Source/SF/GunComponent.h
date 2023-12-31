// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "GunComponent.generated.h"

class AProjectile;
class ABomb;
class AGameplayManager;

USTRUCT(BlueprintType)
struct FGunComponentConfig
{
    GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	bool _DoubleLaser = false;
	UPROPERTY(EditAnywhere)
	float _Speed =0;
	UPROPERTY(EditAnywhere)
	float _ShotSpeedMultiplier =0;
	UPROPERTY(EditAnywhere)
	float _ShotLeadErrorMin = 1.5f;
	UPROPERTY(EditAnywhere)
	float _ShotLeadErrorMax = 1.5f; // 1 for dead on player
	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectile> _ProjectileClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectile> _SecondaryProjectileClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABomb> _BombClass;
	UPROPERTY(EditAnywhere)
	int32 _AvailableAmmo = -1; //negative number for infinite
	UPROPERTY(EditAnywhere)
	int32 _AvailableBombs = -1;
	UPROPERTY(EditAnywhere, Category = "Aiming")
	bool _bUsesWorldRotationWhenAiming= false;;
	UPROPERTY(EditAnywhere)
	USceneComponent *_SingleLaserSpawnPoint = nullptr;
	UPROPERTY(EditAnywhere)
	TArray<USceneComponent *> _LaserSpawnPoints;
    // Add more parameters as needed.
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SF_API UGunComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGunComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY()
	AGameplayManager* GameplayManager;
	bool bUsesWorldRotationWhenAiming= false;

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOutOfAmmoDelegate);
	UPROPERTY(BlueprintAssignable, Category = "Ammo")
	FOutOfAmmoDelegate OutOfAmmoDelegate;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	virtual void SetupGunComponent(FGunComponentConfig *GunConfig);
	
	virtual void SpawnLaser(USceneComponent *SpawnPoint);
	virtual void FireLasers();
	virtual void FireBombs();
	virtual void SpawnBombs(USceneComponent *SpawnPoint);

	virtual void Aim(void (UGunComponent::*FireFunctionPtr)());
	virtual void AimAtPlayer(void (UGunComponent::*FireFunctionPtr)());

	void AddBomb(int32 BombsToAdd);
	bool bIsActive = false;


	UPROPERTY()
	USceneComponent *SingleLaserSpawnPoint;
	UPROPERTY()
	TArray<USceneComponent *> LaserSpawnPoints;
	UPROPERTY()
	AActor *OwnerActor;
	UPROPERTY()
	AActor *PlayerActor;


	bool DoubleLaser = false;

	float Speed;

	float ShotSpeedMultiplier;

	float ShotLeadErrorMin = 1.5f;

	float ShotLeadErrorMax = 1.5f; // 1 for dead on player
	UPROPERTY()
	TSubclassOf<AProjectile> ProjectileClass;
	UPROPERTY()
	TSubclassOf<AProjectile> SecondaryProjectileClass;
	UPROPERTY()
	TSubclassOf<ABomb> BombClass;

	int32 AvailableAmmo = -1; //negative number for infinite

	int32 AvailableBombs = -1;
		
};
