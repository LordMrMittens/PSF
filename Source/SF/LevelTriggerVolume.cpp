// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTriggerVolume.h"

void ALevelTriggerVolume::BeginPlay()
{
    Super::BeginPlay();
    OnActorBeginOverlap.AddDynamic(this, &ALevelTriggerVolume::OnOverlapStart);
}


void ALevelTriggerVolume::OnOverlapStart(AActor* OverlappedActor, AActor* OtherActor)
{

}


