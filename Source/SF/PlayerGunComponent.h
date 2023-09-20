// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GunComponent.h"
#include "PlayerGunComponent.generated.h"

/**
 * 
 */
UCLASS()
class SF_API UPlayerGunComponent : public UGunComponent
{
	GENERATED_BODY()
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	

public:
	void EnhanceLasers();
	void ResetLasers();

	virtual void SpawnLaser(USceneComponent *SpawnPoint) override;
private:
	bool PowerLaser = false;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectile> SecondaryProjectileClass;
	TSubclassOf<AProjectile> ActiveProjectileClass;
	
};
