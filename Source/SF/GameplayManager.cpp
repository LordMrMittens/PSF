// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayManager.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerPawn.h"
#include "ObjectPooler.h"
#include "FlyingEnemyPawn.h"

// Sets default values
AGameplayManager::AGameplayManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameplayManager::BeginPlay()
{
	Super::BeginPlay();
	CreateObjectPools();
}

// Called every frame
void AGameplayManager::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);
	if(PlayerPawn==nullptr){
		PlayerPawn = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
		if (PlayerPawn)
		{
			PlayerPawn->OnPlayerHasDied.AddDynamic(this, &AGameplayManager::RespawningSequence);
			RespawningPoint = DefaultRespawningPoint;
		}
		
	} else {
		UpdatePlayerLocation();
	}

}
void AGameplayManager::UpdatePlayerLocation()
{
	PlayerLocation = PlayerPawn->GetActorLocation();
}

void AGameplayManager::CreateObjectPools()
{
    for (auto& Pair : ObjectPoolerProperties)
    {
        FObjectPoolerProperties& Properties = Pair.Value;
        Properties.ObjectPooler = NewObject<UObjectPooler>();
        Properties.ObjectPooler->ObjectClass = Pair.Key;
        Properties.ObjectPooler->PoolSize = Properties.PoolSize;
        Properties.ObjectPooler->Initialize(GetWorld());
    }
}


void AGameplayManager::RespawningSequence()
{
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &AGameplayManager::RespawnPlayer, RespawnTime, false);
}

void AGameplayManager::RespawnPlayer()
{
	//Move to respawn location
    //Delete spawned enemies
    //Respawn Enemies
    //Repair Ship
    //ResetGun
    //make active
	UE_LOG(LogTemp, Display, TEXT("Player Has Respawned"));
}