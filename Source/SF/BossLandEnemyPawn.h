// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LandEnemyPawn.h"
#include "BossLandEnemyPawn.generated.h"

class AGameplayManager;
class UNiagaraSystem;
/**
 * 
 */
UCLASS()
class SF_API ABossLandEnemyPawn : public ALandEnemyPawn
{
	GENERATED_BODY()
public:
	ABossLandEnemyPawn();
protected:
	virtual void BeginPlay() override;
	virtual void AimAndShoot() override;

public:
	virtual void Tick(float DeltaTime) override;
	bool bShouldAim = true;

	private:
	// Attacking behaviour
	UPROPERTY(EditAnywhere, Category = "Attacking behaviour")
	float AttackFrequency;
	float TimeOfLastAttack = 0;
	FTimerHandle AttackTimerHandle;
	// Main Gun Behaviour
	UPROPERTY(EditAnywhere, Category = "Main gun Behaviour")
	float MainGunShotFrequency;
	UPROPERTY(EditAnywhere, Category = "Main gun Behaviour")
	float MainGunWarningDuration;
	UPROPERTY(EditAnywhere, Category = "Main gun Behaviour")
	float MainGunSutainedDuration;
	float MainGunTimeOfLastShot = 0;
	bool bMainGunIsFiring = false;
	UPROPERTY(EditAnywhere, Category = "Main gun Behaviour")
	bool bShouldMainGunFire = true;
	UPROPERTY(EditAnywhere, Category = "Attacking Effects")
	UNiagaraSystem* WarningLaser;
	void SustainedLaserAttack();
	void ToggleMainLaser();

	
};
