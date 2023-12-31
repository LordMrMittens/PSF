// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bomb.h"
#include "BombEnemyFlak.generated.h"

class AGameplayManager;
/**
 * 
 */
UCLASS()
class SF_API ABombEnemyFlak : public ABomb
{
	GENERATED_BODY()
	
	protected:
	void BeginPlay() override;
	public:
	ABombEnemyFlak();
	void Tick(float DeltaTime) override;
	void SetExplosionLocation(FVector Location);

	private:
	AGameplayManager* GameplayManager;
	float CalculateXDistanceToPlayer();
	float PreviousXDistanceToPlayer = 9999999999;
	UPROPERTY(EditAnywhere, Category = "ExplosionLimits")
	float MinXDistanceToExplode =1000;
	FVector ExplosionLocation = FVector::ZeroVector;
};
