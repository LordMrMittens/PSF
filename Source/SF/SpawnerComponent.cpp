// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnerComponent.h"
#include "Pickup.h"
#include "PlayerPawn.h"
#include "PlayerGunComponent.h"
#include "HealthComponent.h"
#include "GameplayManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USpawnerComponent::USpawnerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void USpawnerComponent::BeginPlay()
{
	Super::BeginPlay();
	GameplayManager = Cast<AGameplayManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AGameplayManager::StaticClass()));
	if (GameplayManager == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("GameplayManager is null"));
	}
	// ...
}

void USpawnerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USpawnerComponent::SpawnObject(FVector SpawnLocation, FRotator SpawnRotation)
{
	if (PickupClass)
	{
		APickup *Pickup = GetWorld()->SpawnActor<APickup>(PickupClass, SpawnLocation, SpawnRotation);
		Pickup->SetUpPickup(DecidePickupType());
	}
}

EPickupType USpawnerComponent::DecidePickupType()
{
	EPickupType TypeToSpawn = EPickupType::BombPickup;
	if (GameplayManager)
	{
		if (GameplayManager->GetPlayerPawn()->GetGunComponent()->GetPowerLaser() == false && GameplayManager->GetPlayerPawn()->GetGunComponent()->getTimeOfLastUpgrade() + MinumumTimeBetweenLaserUpgrades < GetWorld()->GetTimeSeconds())
		{
			TypeToSpawn = EPickupType::LaserUpgrade;
		}
		else if (GameplayManager->GetPlayerPawn()->HealthComponent->GetHealthPercentage() < 0.7f)
		{
			TypeToSpawn = EPickupType::RepairPickup;
		}
		else
		{
			TypeToSpawn = EPickupType::BombPickup;
		}
	}

	return TypeToSpawn;
}
