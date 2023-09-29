// Fill out your copyright notice in the Description page of Project Settings.


#include "FlakGunComponent.h"
#include "GameplayManager.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerPawn.h"
#include "BombEnemyFlak.h"
#include "Projectile.h"

UFlakGunComponent::UFlakGunComponent()
{
    
}

void UFlakGunComponent::Aim(void (UGunComponent::*FireFunctionPtr)())
{
if (!GameplayManager)
    {
        UE_LOG(LogTemp, Error, TEXT("GameplayManager is null"));
        return;
    }

    float LeadFactor = FMath::RandRange(ShotLeadErrorMin, ShotLeadErrorMax);
    FVector PlayerVelocity = GameplayManager->GetPlayerPawn()->GetVelocity();
    FVector GunDirection = FVector(PlayerVelocity.X, 0.f, 0.f) * LeadFactor + GameplayManager->GetPlayerLocation() - GetComponentLocation();
    FRotator NewRotation = GunDirection.Rotation();
	PredictedPlayerLocation = GameplayManager->GetPlayerLocation() + PlayerVelocity * LeadFactor;
    if (bUsesWorldRotationWhenAiming)
    {
        SetWorldRotation(NewRotation);
    }
    else
    {
        SetRelativeRotation(NewRotation);
    }

    (this->*FireFunctionPtr)();
}

void UFlakGunComponent::SpawnBombs(USceneComponent *SpawnPoint)
{
	if(BombClass==nullptr){
		UE_LOG(LogTemp, Error, TEXT("BombClass is null"));
		return;
	}
	if(SpawnPoint==nullptr){
		UE_LOG(LogTemp, Error, TEXT("SpawnPoint is null"));
		return;
	}
	struct FActorSpawnParameters params;
	params.Owner = OwnerActor;
	ABombEnemyFlak *Bomb = GetWorld()->SpawnActor<ABombEnemyFlak>(BombClass,
												SpawnPoint->GetComponentLocation(),
												this->GetComponentRotation(),
												params);
	if (Bomb != nullptr)
	{
		Bomb->SetSpeed(Speed * ShotSpeedMultiplier);
		if(PredictedPlayerLocation != FVector::ZeroVector){
		Bomb->SetExplosionLocation(PredictedPlayerLocation);}
	}
}
