// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTriggerVolume.h"
#include "Kismet/GameplayStatics.h"

void ALevelTriggerVolume::BeginPlay()
{
    Super::BeginPlay();
    OnActorBeginOverlap.AddDynamic(this, &ALevelTriggerVolume::OnOverlapStart);
}
void ALevelTriggerVolume::SpawnEnemy(FVector LocationToSpawn, FRotator RotationToSpawn)
{
    AActor* Enemy = GetWorld()->SpawnActor<AActor>(EnemyClass,
												LocationToSpawn,
												RotationToSpawn
												);
}

void ALevelTriggerVolume::OnOverlapStart(AActor* OverlappedActor, AActor* OtherActor)
{
    if(OtherActor == UGameplayStatics::GetPlayerPawn(GetWorld(),0)){
            for (AActor* SpawnPoint : SpawnPoints)
    {
        SpawnEnemy(SpawnPoint->GetActorLocation(), OtherActor->GetActorRotation());
    }
    }


    
}


