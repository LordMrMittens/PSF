// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBossPawnA.h"


AEnemyBossPawnA::AEnemyBossPawnA()
{
    PrimaryActorTick.bCanEverTick = true;
    MainGunBodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainGunBodyMesh"));
    MainGunBodyMesh->SetupAttachment(GunComponent);
    SecondaryGunComponent = CreateDefaultSubobject<UGunComponent>(TEXT("SecondaryGunComponent"));
    SecondaryGunComponent->SetupAttachment(MainBodyComponent);
    SecondaryGunBodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SecondaryGunBodyMesh"));
    SecondaryGunBodyMesh->SetupAttachment(SecondaryGunComponent);
    TertiaryGunComponent = CreateDefaultSubobject<UGunComponent>(TEXT("TertiaryGunComponent"));
    TertiaryGunComponent->SetupAttachment(MainBodyComponent);
    TertiaryGunBodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TertiaryGunBodyMesh"));
    TertiaryGunBodyMesh->SetupAttachment(TertiaryGunComponent);
}

void AEnemyBossPawnA::BeginPlay()
{
    Super::BeginPlay();
}

void AEnemyBossPawnA::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
