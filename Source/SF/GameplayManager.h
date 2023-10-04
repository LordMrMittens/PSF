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
	UPROPERTY()
	UObjectPooler* FlyingEnemyObjectPooler;
	UPROPERTY(EditAnywhere, Category = "Pooling")
	TSubclassOf<AActor> PoolActorClass;
private:
	//Player Related Variables
	UPROPERTY(VisibleAnywhere, Category = "Player")
	APlayerPawn* PlayerPawn;
	UPROPERTY(VisibleAnywhere, Category = "Player")
	FVector PlayerLocation;

	void UpdatePlayerLocation();

};
