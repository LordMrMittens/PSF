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
    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
    GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &ABossLandEnemyPawn::SustainedLaserAttack, AttackFrequency, true);
}

void ABossLandEnemyPawn::AimAndShoot()
{
        if (IsPlayerInRange()&& ! bIsDead)
    {
        GunComponent->bIsActive = true;
        
    } else{
        GunComponent->bIsActive = false;
    }
}


void ABossLandEnemyPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    AimAndShoot();
    if (bShouldAim)
    {
        GunComponent->AimAtPlayer(nullptr);
    }
    if (bMainGunIsFiring)
    {
        GunComponent->FireLasers();
    }
}

void ABossLandEnemyPawn::SustainedLaserAttack()
{
    FTimerHandle WarningTimerHandle;
    FTimerHandle AttackDurationTimerHandle;
    GetWorldTimerManager().PauseTimer(AttackTimerHandle);
    GetWorldTimerManager().SetTimer(WarningTimerHandle, this, &ABossLandEnemyPawn::ToggleMainLaser, MainGunWarningDuration, false);
    GetWorldTimerManager().SetTimer(AttackDurationTimerHandle, this, &ABossLandEnemyPawn::ToggleMainLaser, MainGunWarningDuration+MainGunSutainedDuration, false);
    UNiagaraFunctionLibrary::SpawnSystemAttached(WarningLaser, SingleLaserSpawnPoint, NAME_None, FVector(0,0,0), GunComponent->GetComponentRotation(), EAttachLocation::KeepRelativeOffset, true);
    
    bShouldAim = true;
}


void ABossLandEnemyPawn::ToggleMainLaser()
{
    if(bMainGunIsFiring){
    MainGunTimeOfLastShot = GetWorld()->GetTimeSeconds();
    GetWorldTimerManager().UnPauseTimer(AttackTimerHandle);
    bShouldAim = false;
    }
    bMainGunIsFiring = !bMainGunIsFiring;
    
}