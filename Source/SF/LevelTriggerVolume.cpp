// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTriggerVolume.h"
#include "GameplayManager.h"
#include "Kismet/GameplayStatics.h"

void ALevelTriggerVolume::BeginPlay()
{
    Super::BeginPlay();
    OnActorBeginOverlap.AddDynamic(this, &ALevelTriggerVolume::OnOverlapStart);
    GameplayManager = Cast<AGameplayManager>(UGameplayStatics::GetActorOfClass(GetWorld(),AGameplayManager::StaticClass()));

}


void ALevelTriggerVolume::OnOverlapStart(AActor* OverlappedActor, AActor* OtherActor)
{

}


