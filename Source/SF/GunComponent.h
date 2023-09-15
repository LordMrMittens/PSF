// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "GunComponent.generated.h"

class AProjectile;

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

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetupGunComponent(AActor* Owner, float ShotSpeed, int32 AmmoAvailable = -1 , bool DoubleShot = false, USceneComponent* SingleLaserSource =nullptr, TArray<USceneComponent*> MultiLasers = TArray<USceneComponent*>());
	void FireLasers();
	void SpawnLaser(USceneComponent* SpawnPoint);
	void Aim(AActor* PlayerActor);

	AActor* OwnerActor;

private:

	USceneComponent* SingleLaserSpawnPoint;
	TArray<USceneComponent*> LaserSpawnPoints;
	float Speed;
	UPROPERTY(EditAnywhere)
	float ShotSpeedMultiplier;
	UPROPERTY(EditAnywhere)
	float ShotLeadMultiplier = 1.5f; //1.5 default
	bool DoubleLaser = false;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectile> ProjectileClass;
	int32 AvailableAmmo = -1;

		
};
