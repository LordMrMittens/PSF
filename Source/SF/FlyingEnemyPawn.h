// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyPawn.h"
#include "FlyingEnemyPawn.generated.h"

class UGunComponent;
/**
 * 
 */
UCLASS()
class SF_API AFlyingEnemyPawn : public AEnemyPawn
{
	GENERATED_BODY()

public:
 AFlyingEnemyPawn();

protected:
	virtual void BeginPlay() override;
	virtual void Move() override;
	virtual void OnDeath() override;

public:
virtual void Tick(float DeltaTime) override;
virtual void ResetPawn() override;

private:

	UPROPERTY(EditAnywhere, Category = "Guns")
	float ShotFrequency;

	FTimerHandle ShotTimerHandle;

	UPROPERTY(EditAnywhere, Category = "Evasion")
	float ObstacleAvoidanceDistance = 5000;

	UPROPERTY(EditAnywhere, Category = "Evasion")
	float ObstacleDetectionFrequency = 1;
	UPROPERTY()
	FTimerHandle ObstacleDetectionTimerHandle;

	UPROPERTY(EditAnywhere, Category = "Evasion")
	float ObstacleAvoidanceDuration = 2;
	UPROPERTY(EditAnywhere, Category = "Evasion")
	float ResetSteeringDuration = 2;
	UPROPERTY(EditAnywhere, Category = "Evasion")
	float ObstacleAvoidanceStrength = 1.5;
	UPROPERTY(EditAnywhere, Category = "Steering")
	float SteerFactor = 3; //times steering force in final script
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
	void ResetEvasion();
	bool DetectObstacles();
	UFUNCTION()
	void LeaveLevel();
	void SteerOffLevel();
	

	UFUNCTION()
	void OnOverlapStart(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
};
