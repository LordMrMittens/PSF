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
	virtual void SetupGunComponent(FGunComponentConfig *GunConfig) override;

	virtual void SpawnLaser(USceneComponent *SpawnPoint) override;

	bool GetPowerLaser() const { return PowerLaser; }
	float getTimeOfLastUpgrade() const { return TimeOfLastUpgrade; }
private:
	bool PowerLaser = false;
	float TimeOfLastUpgrade = 0.0f;

	TSubclassOf<AProjectile> ActiveProjectileClass;
	
};
