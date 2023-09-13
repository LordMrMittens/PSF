// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GunComponent.generated.h"

class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SF_API UGunComponent : public UActorComponent
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
	void SetupGunComponent(float ShotSpeed, bool DoubleShot = false, USceneComponent* SingleLaserSource =nullptr, TArray<USceneComponent*> MultiLasers = TArray<USceneComponent*>());
	void FireLasers();
	void SpawnLaser(USceneComponent* SpawnPoint);

private:

	USceneComponent* SingleLaserSpawnPoint;
	TArray<USceneComponent*> LaserSpawnPoints;
	float Speed;
	bool DoubleLaser = false;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectile> ProjectileClass;
		
};
