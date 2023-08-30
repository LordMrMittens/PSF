// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "InputDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class SF_API UInputDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    class UInputAction* InputSteer;
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    class UInputAction* FireLaser;
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    class UInputAction* FireBombs;
	
};
