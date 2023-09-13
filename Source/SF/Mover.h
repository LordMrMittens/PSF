// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Mover.generated.h"

UCLASS()
class SF_API AMover : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMover();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Move();

	float Speed = 200.0f;
	float Damage;
	FVector Direction = FVector(1,0,0);

};
