// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTrigger_Spawner.h"
#include "Kismet/GameplayStatics.h"


void ALevelTrigger_Spawner::OnOverlapStart(AActor* OverlappedActor, AActor* OtherActor)
{
        if(OtherActor == UGameplayStatics::GetPlayerPawn(GetWorld(),0)){
            for (AActor* SpawnPoint : SpawnPoints)
    {
        SpawnEnemy(SpawnPoint->GetActorLocation(), OtherActor->GetActorRotation());
    }
    }
}
void ALevelTrigger_Spawner::SpawnEnemy(FVector LocationToSpawn, FRotator RotationToSpawn)
{
    AActor* Enemy = GetWorld()->SpawnActor<AActor>(EnemyClass,
												LocationToSpawn,
												RotationToSpawn
												);
}
