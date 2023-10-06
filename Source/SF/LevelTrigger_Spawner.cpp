// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTrigger_Spawner.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyPawn.h"
#include "SpawnerComponent.h"
#include "GameplayManager.h"
#include "ObjectPooler.h"

void ALevelTrigger_Spawner::OnOverlapStart(AActor *OverlappedActor, AActor *OtherActor)
{
    if (OtherActor == UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
    {
        for (AActor *SpawnPoint : SpawnPoints)
        {
            SpawnEnemy(SpawnPoint->GetActorLocation(), OtherActor->GetActorRotation());
        }
    }
}
void ALevelTrigger_Spawner::SpawnEnemy(FVector LocationToSpawn, FRotator RotationToSpawn)
{
    /*
    AEnemyPawn* Enemy = Cast<AEnemyPawn>(GameplayManager->FlyingEnemyObjectPooler->GetObject(LocationToSpawn, RotationToSpawn));
    if(Enemy == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Enemy is null"));
        return;
    }
    Enemy->ResetPawn();
    if (NumberOfEnemiesSpawningPowerUps > 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("OneEnemy Should Spawn PowerUp"));
        Enemy->GetSpawnerComponent()->SetShouldSpawn(true);
        NumberOfEnemiesSpawningPowerUps--;
    }
    */
}
