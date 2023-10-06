// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayManager.generated.h"

class APlayerPawn;
class UObjectPooler;
class AFlyingEnemyPawn;

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
	UObjectPooler* FlyingEnemyObjectPooler;
	UPROPERTY(EditAnywhere, Category = "Pooling")
	TSubclassOf<AActor> FlyingEnemyPoolActorClass;
	UPROPERTY(EditAnywhere, Category = "Pooling")
	int32 FlyingEnemyPoolSize;
	UPROPERTY(EditAnywhere, Category = "Pooling")
	UObjectPooler* LaserObjectPooler;
	UPROPERTY(EditAnywhere, Category = "Pooling")
	TSubclassOf<AActor> LaserPoolActorClass;
	UPROPERTY(EditAnywhere, Category = "Pooling")
	int32 LaserPoolSize;
	UPROPERTY(EditAnywhere, Category = "Pooling")
	UObjectPooler* PowerLaserObjectPooler;
	UPROPERTY(EditAnywhere, Category = "Pooling")
	TSubclassOf<AActor> PowerLaserPoolActorClass;
	UPROPERTY(EditAnywhere, Category = "Pooling")
	int32 PowerLaserPoolSize;
	UPROPERTY(EditAnywhere, Category = "Pooling")
	UObjectPooler* EnemyLaserObjectPooler;
	UPROPERTY(EditAnywhere, Category = "Pooling")
	TSubclassOf<AActor> EnemyLaserPoolActorClass;
	UPROPERTY(EditAnywhere, Category = "Pooling")
	int32 EnemyLaserPoolSize;
	UPROPERTY(EditAnywhere, Category = "Pooling")
	UObjectPooler* HomingMissileObjectPooler;
	UPROPERTY(EditAnywhere, Category = "Pooling")
	TSubclassOf<AActor> HomingMissilePoolActorClass;
	UPROPERTY(EditAnywhere, Category = "Pooling")
	int32 HomingMissilePoolSize;
	UPROPERTY(EditAnywhere, Category = "Pooling")
	UObjectPooler* EnemyFlakObjectPooler;
	UPROPERTY(EditAnywhere, Category = "Pooling")
	TSubclassOf<AActor> EnemyFlakPoolActorClass;
	UPROPERTY(EditAnywhere, Category = "Pooling")
	int32 EnemyFlakPoolSize;
	UPROPERTY(EditAnywhere, Category = "Pooling")
	UObjectPooler* BombsObjectPooler;
	UPROPERTY(EditAnywhere, Category = "Pooling")
	TSubclassOf<AActor> BombsPoolActorClass;
	UPROPERTY(EditAnywhere, Category = "Pooling")
	int32 BombsPoolSize;
	
private:
	//Player Related Variables
	UPROPERTY(VisibleAnywhere, Category = "Player")
	APlayerPawn* PlayerPawn;
	UPROPERTY(VisibleAnywhere, Category = "Player")
	FVector PlayerLocation;

	void UpdatePlayerLocation();
	void CreateObjectPool(UObjectPooler*& OutObjectPooler, TSubclassOf<AActor> PoolActorClass, int32 PoolSize);

};
