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

public:
virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	USceneComponent *SingleLaserSpawnPoint;
	UPROPERTY(EditAnywhere)
	USceneComponent *DoubleLaserSpawnPointL;
	UPROPERTY(EditAnywhere)
	USceneComponent *DoubleLaserSpawnPointR;

	TArray<USceneComponent *> LaserSpawnPoints;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent *MainBodyComponent;
	UPROPERTY(EditAnywhere)
	UGunComponent *GunComponent;
	AActor* PlayerActor;

	UPROPERTY(EditAnywhere)
	float ShotFrequency;

	UPROPERTY(EditAnywhere)
	int32 AmmoAvailable =3;

	FTimerHandle ShotTimerHandle;
	UPROPERTY(EditAnywhere)
	float SteerFactor = 3; //times steering force in final script

	UPROPERTY(EditAnywhere)
	float ObstacleAvoidanceDistance = 5000;

	UPROPERTY(EditAnywhere)
	float ObstacleDetectionFrequency = 1;
	FTimerHandle ObstacleDetectionTimerHandle;

	UPROPERTY(EditAnywhere)
	float ObstacleAvoidanceDuration = 2;
	UPROPERTY(EditAnywhere)
	float ResetSteeringDuration = 4;
	UPROPERTY(EditAnywhere)
	float ObstacleAvoidanceStrength = 1.5;

	UPROPERTY(EditAnywhere)
	float VerticalDistanceToPlayerOffset = 440;
	UPROPERTY(EditAnywhere)
	float HorizontalDistanceToPlayerOffset = 460;
	UPROPERTY(EditAnywhere)
	float DistanceFromBordersffset = 550;


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


	UFUNCTION()
	void OnOverlapStart(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
};
