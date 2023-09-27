// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTrigger_Spawner.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyPawn.h"
#include "SpawnerComponent.h"


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
    AEnemyPawn* Enemy = GetWorld()->SpawnActor<AEnemyPawn>(EnemyClass,
												LocationToSpawn,
												RotationToSpawn
												);
    if (Enemy && NumberOfEnemiesSpawningPowerUps > 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("OneEnemy Should Spawn PowerUp"));
        Enemy->GetSpawnerComponent()->SetShouldSpawn(true);
        NumberOfEnemiesSpawningPowerUps--;
    }
    
}
