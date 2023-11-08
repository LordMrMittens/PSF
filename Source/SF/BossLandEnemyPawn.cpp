// Fill out your copyright notice in the Description page of Project Settings.


#include "BossLandEnemyPawn.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"


ABossLandEnemyPawn::ABossLandEnemyPawn()
{
    
}

void ABossLandEnemyPawn::BeginPlay()
{
    Super::BeginPlay();
    GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &ABossLandEnemyPawn::SustainedLaserAttack, AttackFrequency, true);
}



void ABossLandEnemyPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ABossLandEnemyPawn::SustainedLaserAttack()
{
    FTimerHandle WarningTimerHandle;
    FTimerHandle AttackDurationTimerHandle;
    GetWorldTimerManager().PauseTimer(AttackTimerHandle);
    GetWorldTimerManager().SetTimer(WarningTimerHandle, this, &ABossLandEnemyPawn::ToggleMainLaser, MainGunWarningDuration, false);
    GetWorldTimerManager().SetTimer(AttackDurationTimerHandle, this, &ABossLandEnemyPawn::ToggleMainLaser, MainGunWarningDuration+MainGunSutainedDuration, false);
    UNiagaraFunctionLibrary::SpawnSystemAttached(WarningLaser, SingleLaserSpawnPoint, NAME_None, FVector(0,0,0), FRotator(0,0,0), EAttachLocation::KeepRelativeOffset, true);
    GunComponent->Aim(nullptr);
    UE_LOG(LogTemp, Error, TEXT("Aiming warning"));
}


void ABossLandEnemyPawn::ToggleMainLaser()
{
        if(bMainGunIsFiring){
    MainGunTimeOfLastShot = GetWorld()->GetTimeSeconds();
    GetWorldTimerManager().UnPauseTimer(AttackTimerHandle);
    }
    bMainGunIsFiring = !bMainGunIsFiring;
    UE_LOG(LogTemp, Error, TEXT("Shooting"));
}