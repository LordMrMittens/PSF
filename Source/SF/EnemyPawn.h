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
public:
UPROPERTY(EditAnywhere, Category = "Components")
	USpawnerComponent* SpawnerComponent;
	
};
