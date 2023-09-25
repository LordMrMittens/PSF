// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "LevelTriggerVolume.generated.h"

/**
 * 
 */
UCLASS()
class SF_API ALevelTriggerVolume : public ATriggerBox
{
	GENERATED_BODY()

protected:
virtual void BeginPlay() override;
UFUNCTION()
virtual void OnOverlapStart(AActor* OverlappedActor, AActor* OtherActor);

public:

private:




};
