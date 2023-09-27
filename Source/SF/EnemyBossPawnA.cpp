// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBossPawnA.h"
#include "GunComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameplayManager.h"
#include "PlayerPawn.h"
#include "HealthComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"


AEnemyBossPawnA::AEnemyBossPawnA()
{
    PrimaryActorTick.bCanEverTick = true;

    MainGunBodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainGunBodyMesh"));
    MainGunBodyMesh->SetupAttachment(GunComponent);

    SecondaryGunComponent = CreateDefaultSubobject<UGunComponent>(TEXT("SecondaryGunComponent"));
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
    if (GunComponent && bMainGunIsFiring){
        GunComponent->FireLasers();
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

        }
        if (GunToUse == TertiaryGunComponent)
        {
            
        }
        
    }
}

UGunComponent* AEnemyBossPawnA::DetermineGunToUse()
{
    if( MainGunTimeOfLastShot == 0 || MainGunTimeOfLastShot + MainGunShotFrequency < GetWorld()->GetTimeSeconds()){
        MainGunTimeOfLastShot = -1;
        return GunComponent;
    } else if(SecondaryGunTimeOfLastShot == 0 || SecondaryGunTimeOfLastShot + SecondaryGunShotFrequency < GetWorld()->GetTimeSeconds()){
        SecondaryGunTimeOfLastShot = GetWorld()->GetTimeSeconds();
        return SecondaryGunComponent;
    } else if(TertiaryGunTimeOfLastShot == 0 || TertiaryGunTimeOfLastShot + TertiaryGunShotFrequency < GetWorld()->GetTimeSeconds()){
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
    //move to players YZ coords
    GetWorldTimerManager().PauseTimer(AttackTimerHandle);
    
    GetWorldTimerManager().SetTimer(WarningTimerHandle, this, &AEnemyBossPawnA::ToggleMainLaser, MainGunWarningDuration, false);
    GetWorldTimerManager().SetTimer(AttackDurationTimerHandle, this, &AEnemyBossPawnA::ToggleMainLaser, MainGunWarningDuration+MainGunSutainedDuration, false);
    UNiagaraFunctionLibrary::SpawnSystemAttached(WarningLaser, SingleLaserSpawnPoint, NAME_None, FVector(0,0,0), FRotator(0,0,0), EAttachLocation::KeepRelativeOffset, true);
    
    ///GetWorld()->SpawnActor(); //spawn Warning Laser from single laser spawnpoint need new asset

}

void AEnemyBossPawnA::FlakCannonsAttack()
{
    
}

void AEnemyBossPawnA::MissileAttack()
{
    
}

void AEnemyBossPawnA::ToggleMainLaser()
{
    if(bMainGunIsFiring){
    MainGunTimeOfLastShot = GetWorld()->GetTimeSeconds();
    GetWorldTimerManager().UnPauseTimer(AttackTimerHandle);
    }
    bMainGunIsFiring = !bMainGunIsFiring;
}
