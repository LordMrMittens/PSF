// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovingPawn.h"
#include "EnemyPawn.generated.h"

class USpawnerComponent;
/**
 * 
 */
UCLASS()
class SF_API AEnemyPawn : public AMovingPawn
{
	GENERATED_BODY()

public:
	AEnemyPawn();
protected:
	virtual void OnDeath() override;
	virtual float CalculateTargetVelocity();
public:
UPROPERTY(EditAnywhere, Category = "Components")
	USpawnerComponent* SpawnerComponent;

UPROPERTY(EditAnywhere, Category="Movement")
	float MaxTargetDistanceFromPlayer = 5000;
	UPROPERTY(EditAnywhere, Category="Movement")
	float MinTargetDistanceFromPlayer = 2500;
};
