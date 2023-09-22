// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SFGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class SF_API ASFGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	FVector GetMinBoundary() const
	{
		return MinBoundary;
	}
	FVector GetMaxBoundary() const
	{
		return MaxBoundary;
	}
		FVector GetMoveDirection() const
	{
		return MoveDirection;
	}
	float GetSpeed() const
	{
		return Speed;
	}

private:
	UPROPERTY(EditAnywhere, Category = "Level Movement")
	float Speed = 3000;
	UPROPERTY(EditAnywhere, Category = "Level Movement")
	FVector MoveDirection;
	UPROPERTY(EditAnywhere, Category = "Level Boundaries")
	FVector MinBoundary = FVector(0.0f, -5000.0f, 0.0f);
	UPROPERTY(EditAnywhere, Category = "Level Boundaries")
	FVector MaxBoundary = FVector(0.0f, 5000.0f, 5000.0f);
};
