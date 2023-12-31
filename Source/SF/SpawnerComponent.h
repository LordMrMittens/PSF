// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpawnerComponent.generated.h"

class	APickup;
class AGameplayManager;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SF_API USpawnerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpawnerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SpawnObject(FVector SpawnLocation, FRotator SpawnRotation);
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<APickup> PickupClass;
	void SetShouldSpawn(bool _bShouldSpawn) {bShouldSpawn = _bShouldSpawn;}

private:
	UFUNCTION()
	EPickupType DecidePickupType();
	UPROPERTY(EditAnywhere, Category = "Spawning")
	EPickupType SpawnedPickupType;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	float MinumumTimeBetweenLaserUpgrades = 10.0f;

	AGameplayManager* GameplayManager;
	UPROPERTY(VisibleAnywhere)
	bool bShouldSpawn;
};
