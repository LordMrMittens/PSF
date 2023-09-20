// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MovingPawn.generated.h"

class UHealthComponent;

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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float Speed;
	UPROPERTY(EditAnywhere)
	FVector MoveDirection;
	FVector OriginalMoveDirection;
	UPROPERTY(EditAnywhere)
	float MaxTiltAngle;
	UPROPERTY(EditAnywhere)
	float RotationInterpSpeed;

	UHealthComponent* HealthComponent;

	UFUNCTION()
	void OnDeath();

	FVector MinBoundary;
    FVector MaxBoundary;

};
