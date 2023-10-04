// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelTriggerVolume.h"
#include "LevelTrigger_Spawner.generated.h"

class AGameplayManager;
/**
 * 
 */
UCLASS()
class SF_API ALevelTrigger_Spawner : public ALevelTriggerVolume
{
	GENERATED_BODY()
	protected:

	virtual void OnOverlapStart(AActor* OverlappedActor, AActor* OtherActor) override;
public:

UPROPERTY(EditAnywhere, Category = "Spawning", meta = (ToolTip = "If spawning powerups is enabled, the enemy that will spawn the powerup will be spawned on the first position in this array"))
TArray<AActor*> SpawnPoints;
UPROPERTY(EditAnywhere, Category = "Spawning")
TSubclassOf<AActor> EnemyClass;
UPROPERTY(EditAnywhere, Category="PowerUps")
int32 NumberOfEnemiesSpawningPowerUps = 1;

UPROPERTY()
AGameplayManager* GameplayManager;

void SpawnEnemy(FVector LocationToSpawn, FRotator RotationToSpawn);

};
