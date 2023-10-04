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
    FlyingEnemyObjectPooler = NewObject<UObjectPooler>();
    FlyingEnemyObjectPooler->ObjectClass = PoolActorClass;
    FlyingEnemyObjectPooler->PoolSize = 10;
    FlyingEnemyObjectPooler->Initialize(GetWorld());
}

// Called every frame
void AGameplayManager::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);
	if(PlayerPawn==nullptr){
		PlayerPawn = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	} else {
		UpdatePlayerLocation();
	}

}

void AGameplayManager::UpdatePlayerLocation()
{
	PlayerLocation = PlayerPawn->GetActorLocation();
}

