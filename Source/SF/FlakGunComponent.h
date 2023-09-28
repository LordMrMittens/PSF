// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GunComponent.h"
#include "FlakGunComponent.generated.h"

class AGameplayManager;
/**
 * 
 */
UCLASS()
class SF_API UFlakGunComponent : public UGunComponent
{
	GENERATED_BODY()

	public:
	UFlakGunComponent();
	virtual void Aim(void (UGunComponent::*FireFunctionPtr)());


	
	
};
