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

	void Steer();
};
