// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovingPawn.h"
#include "FlyingEnemyPawn.generated.h"

class UGunComponent;
/**
 * 
 */
UCLASS()
class SF_API AFlyingEnemyPawn : public AMovingPawn
{
	GENERATED_BODY()

public:
 AFlyingEnemyPawn();

protected:
	virtual void BeginPlay() override;
	virtual void Move() override;

public:
virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent *SingleLaserSpawnPoint;
	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent *DoubleLaserSpawnPointL;
	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent *DoubleLaserSpawnPointR;

	TArray<USceneComponent *> LaserSpawnPoints;
	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent *MainBodyComponent;
	UPROPERTY(EditAnywhere, Category = "Components")
	UGunComponent *GunComponent;
	AActor* PlayerActor;

	UPROPERTY(EditAnywhere, Category = "Guns")
	float ShotFrequency;

	UPROPERTY(EditAnywhere, Category = "Guns")
	int32 AmmoAvailable =3;

	FTimerHandle ShotTimerHandle;
	UPROPERTY(EditAnywhere, Category = "Guns")
	float SteerFactor = 3; //times steering force in final script

	UPROPERTY(EditAnywhere, Category = "Evasion")
	float ObstacleAvoidanceDistance = 5000;

	UPROPERTY(EditAnywhere, Category = "Evasion")
	float ObstacleDetectionFrequency = 1;
	FTimerHandle ObstacleDetectionTimerHandle;

	UPROPERTY(EditAnywhere, Category = "Evasion")
	float ObstacleAvoidanceDuration = 2;
	UPROPERTY(EditAnywhere, Category = "Evasion")
	float ResetSteeringDuration = 4;
	UPROPERTY(EditAnywhere, Category = "Evasion")
	float ObstacleAvoidanceStrength = 1.5;

	UPROPERTY(EditAnywhere, Category = "Steering")
	float VerticalDistanceToPlayerOffset = 440;
	UPROPERTY(EditAnywhere, Category = "Steering")
	float HorizontalDistanceToPlayerOffset = 460;
	UPROPERTY(EditAnywhere, Category = "Steering")
	float DistanceFromBordersffset = 550; // not implemented yet

	FTimerHandle LeavingDelayTimerHandle;
	UPROPERTY(EditAnywhere, Category = "Steering")
	float HoldTimeBeforeLevelExit = 3;
	UPROPERTY(EditAnywhere, Category = "Misc")
	float TimeToDestroyWhenLeaving = 15; // not implemented yet


	float ZObstacleAvoidanceStrength =.0f;
	float ObstacleAvoidanceTimer = 0;
	bool CanSteerTowardsPlayer = true;
	bool LeavingLevel = false;
	bool PerformEvasiveManouevres = false;

	int32 ObstacleAvoidanceDirection = 0;

	void Steer();
	void Evade();
	bool DetectObstacles();
	UFUNCTION()
	void LeaveLevel();
	void SteerOffLevel();


	UFUNCTION()
	void OnOverlapStart(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
};
