// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyPawn.h"
#include "LandEnemyPawn.generated.h"

class UGunComponent;
class UCapsuleComponent;
/**
 *
 */
UCLASS()
class SF_API ALandEnemyPawn : public AEnemyPawn
{
	GENERATED_BODY()

public:
	ALandEnemyPawn();

protected:
	virtual void BeginPlay() override;
	virtual void Move() override;
	

public:
	virtual void Tick(float DeltaTime) override;

private:
	AActor* SetTarget();
	bool RotationSet();
	bool IsPlayerInRange() const;

	void AimAndShoot();

	UPROPERTY(EditAnywhere)
	UCapsuleComponent *CapsuleComponent;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* TurretMeshComponent;

	UPROPERTY(EditAnywhere, Category = "Movement")
	TArray<AActor *> MovementNodes;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MinimumDistanceToTarget;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementSpeed;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float RotationInterpolationSpeed;

	AActor* CurrentTarget;
	AActor* PlayerActor;
	int32 CurrentTargetIndex;
	UPROPERTY(EditAnywhere, Category = "Movement")
	bool bLoopsPositions = false;
	bool bReturning = false;
	bool bStayInPosition = false;

	FTimerHandle ShotTimerHandle;
	UPROPERTY(EditAnywhere, Category = "Shooting")
	float ShotFrequency = 1;
	UPROPERTY(EditAnywhere, Category = "Shooting")
	float ActiveDistance = 10000;


};
