// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BossEnemyPawn.h"
#include "EnemyBossPawnA.generated.h"

class AGameplayManager;
/**
 *
 */
UCLASS()
class SF_API AEnemyBossPawnA : public ABossEnemyPawn
{
	GENERATED_BODY()
public:
	AEnemyBossPawnA();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent *MainGunBodyMesh;
	
	UPROPERTY(EditAnywhere, Category = "Components")
	UGunComponent *SecondaryGunComponent;
	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent *SecondaryGunBodyMesh;
	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent *SecondarySingleLaserSpawnPoint;
	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent *SecondaryDoubleLaserSpawnPointL;
	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent *SecondaryDoubleLaserSpawnPointR;
	TArray<USceneComponent *> SecondaryLaserSpawnPoints;

	UPROPERTY(EditAnywhere, Category = "Guns")
	FGunComponentConfig SecondaryGunConfiguration;

	UPROPERTY(EditAnywhere, Category = "Components")
	UGunComponent *TertiaryGunComponent;
	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent *TertiaryGunBodyMesh;
	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent *TertiarySingleLaserSpawnPoint;
	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent *TertiaryDoubleLaserSpawnPointL;
	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent *TertiaryDoubleLaserSpawnPointR;
	TArray<USceneComponent *> TertiaryLaserSpawnPoints;

	UPROPERTY(EditAnywhere, Category = "Guns")
	FGunComponentConfig TertiaryGunConfiguration;

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
	float MainGunTimeOfLastShot =0;
	bool bMainGunIsFiring = false;

	// Secondary Gun Behaviour
	UPROPERTY(EditAnywhere, Category = "Secondary gun Behaviour")
	float SecondaryGunShotFrequency;
	UPROPERTY(EditAnywhere, Category = "Secondary gun Behaviour")
	float SecondaryGunWarningDuration;
	UPROPERTY(EditAnywhere, Category = "Secondary gun Behaviour")
	float SecondaryGunSutainedDuration;
	float SecondaryGunTimeOfLastShot = 0;
	// Tertiary Gun Behaviour
	UPROPERTY(EditAnywhere, Category = "Tertiary gun Behaviour")
	float TertiaryGunShotFrequency;
	UPROPERTY(EditAnywhere, Category = "Tertiary gun Behaviour")
	float TertiaryGunWarningDuration;
	UPROPERTY(EditAnywhere, Category = "Tertiary gun Behaviour")
	float TertiaryGunSutainedDuration;
	float TertiaryGunTimeOfLastShot = 0;

	UFUNCTION()
	void OnOverlapStart(class UPrimitiveComponent *OverlappedComp, class AActor *OtherActor, class UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	UFUNCTION()
	void Attack();
	void SustainedLaserAttack();
	void FlakCannonsAttack();
	void MissileAttack();
	void ToggleMainLaser();
	UGunComponent* DetermineGunToUse();
};
