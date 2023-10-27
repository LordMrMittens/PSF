// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayManager.generated.h"

class APlayerPawn;
class UObjectPooler;
class AFlyingEnemyPawn;

USTRUCT(BlueprintType)
struct FObjectPoolerProperties
{
    GENERATED_BODY()

	public:

    UPROPERTY(EditAnywhere, Category = "Pooling")
    UObjectPooler* ObjectPooler;

    UPROPERTY(EditAnywhere, Category = "Pooling")
    int32 PoolSize;
};

UCLASS()
class SF_API AGameplayManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameplayManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector GetPlayerLocation() const{
		return PlayerLocation;
	}
	APlayerPawn* GetPlayerPawn(){
		return PlayerPawn;
	}

	UPROPERTY(EditAnywhere, Category = "Pooling")
	TMap<TSubclassOf<AActor>, FObjectPoolerProperties> ObjectPoolerProperties;
	void SetSpawningPoint(AActor* SpawnPoint) {RespawningPoint = SpawnPoint;}
	
private:
	//Player Related Variables
	UPROPERTY(VisibleAnywhere, Category = "Player")
	APlayerPawn* PlayerPawn;
	UPROPERTY(VisibleAnywhere, Category = "Player")
	FVector PlayerLocation;

	UPROPERTY()
	FTimerHandle RespawnTimerHandle;
	UPROPERTY(EditAnywhere, Category = "Respawn")
	float RespawnTime = 3;
	UPROPERTY(EditAnywhere, Category = "Respawn")
	AActor * RespawningPoint;

	void UpdatePlayerLocation();
	void CreateObjectPools();
	UFUNCTION()
	void RespawningSequence();
	UFUNCTION()
	void RespawnPlayer();

	

};
