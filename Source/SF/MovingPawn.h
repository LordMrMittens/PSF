// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GunComponent.h"
#include "HealthComponent.h"
#include "GameFramework/Pawn.h"
#include "MovingPawn.generated.h"

class UGunComponent;
class UHealthComponent;
class AGameplayManager;

UCLASS()
class SF_API AMovingPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMovingPawn();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeactivationDelegate, AActor*, Pawn);
	FOnDeactivationDelegate OnActorHasDeactivated;

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Move();
	virtual void SetRotation();
	virtual void SetLevelBoundary();
	virtual void LimitMovement(FVector CurrentActorLocation, FVector& MovementDelta);
	virtual void CheckIfOutOfBounds(FVector CurrentActorLocation, FVector& MovementDelta);
	
	UFUNCTION()
	virtual void OnDeath();

	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent *SingleLaserSpawnPoint;
	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent *DoubleLaserSpawnPointL;
	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent *DoubleLaserSpawnPointR;
	TArray<USceneComponent *> LaserSpawnPoints;
	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent *MainBodyComponent;
	UPROPERTY(EditAnywhere, Category = "Components")
	UGunComponent *GunComponent;

	
	FTimerHandle DeactivateTimerHandle;
	UPROPERTY(EditAnywhere)
	bool bIsActive = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void ResetPawn();
	void SetActive(bool IsActive) { bIsActive = IsActive; }
	void DeactivatePawn();
	float Speed;
	float CurrentSpeed;
	FVector MoveDirection;
	FVector OriginalMoveDirection;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MaxTiltAngle;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float RotationInterpSpeed;

	UPROPERTY(EditAnywhere, Category = "Guns")
	FGunComponentConfig GunConfiguration;

	UPROPERTY(EditAnywhere, Category = "Components")
	UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, Category = "Health")
	FHealthComponentConfig HealthConfiguration;



	FVector MinBoundary;
    FVector MaxBoundary;
	UPROPERTY()
	AGameplayManager* GameplayManager;

};
