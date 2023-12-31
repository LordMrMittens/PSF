// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBossPawnA.h"
#include "GunComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameplayManager.h"
#include "PlayerPawn.h"
#include "HealthComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "FlakGunComponent.h"


AEnemyBossPawnA::AEnemyBossPawnA()
{
    PrimaryActorTick.bCanEverTick = true;

    MainGunBodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainGunBodyMesh"));
    MainGunBodyMesh->SetupAttachment(GunComponent);

    SecondaryGunComponent = CreateDefaultSubobject<UFlakGunComponent>(TEXT("SecondaryGunComponent"));
    SecondaryGunComponent->SetupAttachment(MainBodyComponent);
    SecondaryGunBodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SecondaryGunBodyMesh"));
    SecondaryGunBodyMesh->SetupAttachment(SecondaryGunComponent);
    SecondarySingleLaserSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SecondarySingleLaserSpawnPoint"));
    SecondarySingleLaserSpawnPoint->SetupAttachment(SecondaryGunComponent);
    SecondaryDoubleLaserSpawnPointL = CreateDefaultSubobject<USceneComponent>(TEXT("SecondaryDoubleLaserSpawnPointL"));
    SecondaryDoubleLaserSpawnPointL->SetupAttachment(SecondaryGunComponent);
    SecondaryLaserSpawnPoints.Add(SecondaryDoubleLaserSpawnPointL);
    SecondaryDoubleLaserSpawnPointR = CreateDefaultSubobject<USceneComponent>(TEXT("SecondaryDoubleLaserSpawnPointR"));
    SecondaryDoubleLaserSpawnPointR->SetupAttachment(SecondaryGunComponent);
    SecondaryLaserSpawnPoints.Add(SecondaryDoubleLaserSpawnPointR);

    TertiaryGunComponent = CreateDefaultSubobject<UGunComponent>(TEXT("TertiaryGunComponent"));
    TertiaryGunComponent->SetupAttachment(MainBodyComponent);
    TertiaryGunBodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TertiaryGunBodyMesh"));
    TertiaryGunBodyMesh->SetupAttachment(TertiaryGunComponent);
    TertiarySingleLaserSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("TertiarySingleLaserSpawnPoint"));
    TertiarySingleLaserSpawnPoint->SetupAttachment(TertiaryGunComponent);
    TertiaryDoubleLaserSpawnPointL = CreateDefaultSubobject<USceneComponent>(TEXT("TertiaryDoubleLaserSpawnPointL"));
    TertiaryDoubleLaserSpawnPointL->SetupAttachment(TertiaryGunComponent);
    TertiaryLaserSpawnPoints.Add(TertiaryDoubleLaserSpawnPointL);
    TertiaryDoubleLaserSpawnPointR = CreateDefaultSubobject<USceneComponent>(TEXT("TertiaryDoubleLaserSpawnPointR"));
    TertiaryDoubleLaserSpawnPointR->SetupAttachment(TertiaryGunComponent);
    TertiaryLaserSpawnPoints.Add(TertiaryDoubleLaserSpawnPointR);

}

void AEnemyBossPawnA::BeginPlay()
{
    Super::BeginPlay();
    if(GameplayManager){
    PlayerActor = Cast<AActor>(GameplayManager->GetPlayerPawn());
}
    if(MainBodyComponent){
    		MainBodyComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBossPawnA::OnOverlapStart);
	}
    if(SecondaryGunComponent){
        SecondaryGunConfiguration._SingleLaserSpawnPoint = SecondarySingleLaserSpawnPoint;
        SecondaryGunConfiguration._LaserSpawnPoints = SecondaryLaserSpawnPoints;
        SecondaryGunConfiguration._Speed = Speed;
        SecondaryGunComponent->SetupGunComponent(&SecondaryGunConfiguration);
    }
    if (TertiaryGunComponent)
    {
        TertiaryGunConfiguration._SingleLaserSpawnPoint = TertiarySingleLaserSpawnPoint;
        TertiaryGunConfiguration._LaserSpawnPoints = TertiaryLaserSpawnPoints;
        TertiaryGunConfiguration._Speed = Speed;
        TertiaryGunComponent->SetupGunComponent(&TertiaryGunConfiguration);
    }
    GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &AEnemyBossPawnA::Attack, AttackFrequency, true);
}

void AEnemyBossPawnA::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (bIsSteeringTowardsPlayer)
    {
        SteerTowardsPlayer();
    }
    if (GunComponent)
    {
        if (bMainGunIsFiring)
        {
            GunComponent->FireLasers();
        }
        if (bIsAttackingWithFlak)
        {
            FlakCannonsAttack();
        }
        if(bIsAttackingWithMissiles){
            MissileAttack();
        }
    }
}

void AEnemyBossPawnA::OnOverlapStart(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    
}

void AEnemyBossPawnA::Attack()
{
    UGunComponent* GunToUse = DetermineGunToUse();
    if (GunToUse != nullptr)
    {
        if(GunToUse == GunComponent){
            SustainedLaserAttack();
        }
        if(GunToUse == SecondaryGunComponent){
            FlakCannonsAttack();
        }
        if (GunToUse == TertiaryGunComponent)
        {
            MissileAttack();
        }
        
    }
}

UGunComponent* AEnemyBossPawnA::DetermineGunToUse()
{
    if(bShouldMainGunFire && (MainGunTimeOfLastShot == 0 || MainGunTimeOfLastShot + MainGunShotFrequency < GetWorld()->GetTimeSeconds())){
        MainGunTimeOfLastShot = -1;
        return GunComponent;
    } else if(bShouldSecondaryGunFire && (SecondaryGunTimeOfLastShot == 0 || SecondaryGunTimeOfLastShot + SecondaryGunShotFrequency < GetWorld()->GetTimeSeconds())){
        return SecondaryGunComponent;
    } else if(bShouldTertiaryGunFire && (TertiaryGunTimeOfLastShot == 0 || TertiaryGunTimeOfLastShot + TertiaryGunShotFrequency < GetWorld()->GetTimeSeconds())){
        TertiaryGunTimeOfLastShot = GetWorld()->GetTimeSeconds();
        return TertiaryGunComponent;
    } else {
        return nullptr;
    }
}

void AEnemyBossPawnA::SustainedLaserAttack()
{
    FTimerHandle WarningTimerHandle;
    FTimerHandle AttackDurationTimerHandle;
    bIsSteeringTowardsPlayer = true;
    GetWorldTimerManager().PauseTimer(AttackTimerHandle);
    GetWorldTimerManager().SetTimer(WarningTimerHandle, this, &AEnemyBossPawnA::ToggleMainLaser, MainGunWarningDuration, false);
    GetWorldTimerManager().SetTimer(AttackDurationTimerHandle, this, &AEnemyBossPawnA::ToggleMainLaser, MainGunWarningDuration+MainGunSutainedDuration, false);
    UNiagaraFunctionLibrary::SpawnSystemAttached(WarningLaser, SingleLaserSpawnPoint, NAME_None, FVector(0,0,0), FRotator(0,0,0), EAttachLocation::KeepRelativeOffset, true);
}

void AEnemyBossPawnA::FlakCannonsAttack()
{
    GetWorldTimerManager().PauseTimer(AttackTimerHandle);
    if (TimeOfLastShot == 0 || TimeOfLastShot + TimeBetweenShots < GetWorld()->GetTimeSeconds())
    {
        if (SecondaryGunShotsFired < SecondaryGunShotsInBurst)
        {
            SecondaryGunComponent->Aim(&UGunComponent::FireBombs);
            TimeOfLastShot = GetWorld()->GetTimeSeconds();
            SecondaryGunShotsFired++;
        }
        if (SecondaryGunShotsFired >= SecondaryGunShotsInBurst)
        {
            SecondaryGunShotsFired = 0;
            SecondaryGunTimeOfLastShot = GetWorld()->GetTimeSeconds();
            GetWorldTimerManager().UnPauseTimer(AttackTimerHandle);
            bIsAttackingWithFlak = false;
        }
        else
        {
            bIsAttackingWithFlak = true;
        }
    }
}

void AEnemyBossPawnA::MissileAttack()
{
        GetWorldTimerManager().PauseTimer(AttackTimerHandle);
    if (TimeOfLastMissile == 0 || TimeOfLastMissile + TimeBetweenMissiles < GetWorld()->GetTimeSeconds())
    {
        if (TertiaryGunShotsFired < TertiaryGunShotsInBurst)
        {
            TertiaryGunComponent->FireLasers();
            TimeOfLastMissile = GetWorld()->GetTimeSeconds();
            TertiaryGunShotsFired++;
        }
        if (TertiaryGunShotsFired >= TertiaryGunShotsInBurst)
        {
            TertiaryGunShotsFired = 0;
            TertiaryGunTimeOfLastShot = GetWorld()->GetTimeSeconds();
            GetWorldTimerManager().UnPauseTimer(AttackTimerHandle);
            bIsAttackingWithMissiles = false;
        }
        else
        {
            bIsAttackingWithMissiles = true;
        }
    }
    
}

void AEnemyBossPawnA::ToggleMainLaser()
{
    if(bMainGunIsFiring){
    MainGunTimeOfLastShot = GetWorld()->GetTimeSeconds();
    GetWorldTimerManager().UnPauseTimer(AttackTimerHandle);
    bIsSteeringTowardsPlayer = false;
    }
    bMainGunIsFiring = !bMainGunIsFiring;
}

void AEnemyBossPawnA::SteerTowardsPlayer()
{
     FVector PlayerLocation = GameplayManager->GetPlayerLocation();
        FVector EnemyLocation = GetActorLocation();
        FVector PlayerDirection = (PlayerLocation - EnemyLocation).GetSafeNormal();
            MoveDirection.Z = PlayerDirection.Z * SteerFactor;
            MoveDirection.Y = PlayerDirection.Y * SteerFactor;
}
