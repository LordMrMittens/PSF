// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelTriggerVolume.h"
#include "LevelTrigger_Spawner.generated.h"

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

UPROPERTY(EditAnywhere)
TArray<AActor*> SpawnPoints;
UPROPERTY(EditAnywhere)
TSubclassOf<AActor> EnemyClass;

void SpawnEnemy(FVector LocationToSpawn, FRotator RotationToSpawn);
};
