// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MovingPawn.generated.h"

class UHealthComponent;
class AGameplayManager;

UCLASS()
class SF_API AMovingPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMovingPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Move();
	virtual void SetRotation();
	virtual void SetLevelBoundary();
	virtual void LimitMovement(FVector CurrentActorLocation, FVector& MovementDelta);
	virtual void CheckIfOutOfBounds(FVector CurrentActorLocation, FVector& MovementDelta);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float Speed;
	float CurrentSpeed;
	FVector MoveDirection;
	FVector OriginalMoveDirection;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MaxTiltAngle;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float RotationInterpSpeed;

	UHealthComponent* HealthComponent;

	UFUNCTION()
	void OnDeath();

	FVector MinBoundary;
    FVector MaxBoundary;
	AGameplayManager* GameplayManager;

};
