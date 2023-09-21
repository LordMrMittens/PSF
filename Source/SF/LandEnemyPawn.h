// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovingPawn.h"
#include "LandEnemyPawn.generated.h"

class UGunComponent;
class UCapsuleComponent;
/**
 *
 */
UCLASS()
class SF_API ALandEnemyPawn : public AMovingPawn
{
	GENERATED_BODY()

public:
	ALandEnemyPawn();

protected:
	virtual void BeginPlay() override;
	virtual void Move() override;
	virtual void SetRotation() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	
	UPROPERTY(EditAnywhere)
	UCapsuleComponent *CapsuleComponent;

	UPROPERTY(EditAnywhere)
	USceneComponent* SingleLaserSpawnPoint;
	UPROPERTY(EditAnywhere)
	USceneComponent* DoubleLaserSpawnPointL;
	UPROPERTY(EditAnywhere)
	USceneComponent* DoubleLaserSpawnPointR;
	TArray<USceneComponent*> LaserSpawnPoints;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MainBodyComponent;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* TurretMeshComponent;

	UPROPERTY(EditAnywhere)
	UGunComponent *GunComponent;

	UPROPERTY(EditAnywhere)
	TArray<AActor *> MovementNodes;

	AActor* CurrentTarget;
	int32 CurrentTargetIndex;
	UPROPERTY(EditAnywhere)
	bool bLoopsPositions = false;


};
