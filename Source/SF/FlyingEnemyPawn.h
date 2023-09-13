// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovingPawn.h"
#include "FlyingEnemyPawn.generated.h"

/**
 * 
 */
UCLASS()
class SF_API AFlyingEnemyPawn : public AMovingPawn
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:

private:


	
};
