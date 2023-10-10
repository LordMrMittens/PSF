// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPawn.h"
#include "HealthComponent.h"
#include "SFGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameplayManager.h"
#include "GunComponent.h"
#include "ObjectPooler.h"

// Sets default values
AMovingPawn::AMovingPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
     MainBodyComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainBody"));
    SetRootComponent(MainBodyComponent);

    SingleLaserSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("LaserSpawnPoint"));
    SingleLaserSpawnPoint->SetupAttachment(MainBodyComponent);

    DoubleLaserSpawnPointL = CreateDefaultSubobject<USceneComponent>(TEXT("LaserSpawnPointL"));
    DoubleLaserSpawnPointL->SetupAttachment(MainBodyComponent);
    LaserSpawnPoints.Add(DoubleLaserSpawnPointL);

    DoubleLaserSpawnPointR = CreateDefaultSubobject<USceneComponent>(TEXT("LaserSpawnPointR"));
    DoubleLaserSpawnPointR->SetupAttachment(MainBodyComponent);
    LaserSpawnPoints.Add(DoubleLaserSpawnPointR);

    GunComponent = CreateDefaultSubobject<UGunComponent>(TEXT("Gun"));
    GunComponent->SetupAttachment(MainBodyComponent);

    HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
    
}
// Called when the game starts or when spawned
void AMovingPawn::BeginPlay()
{
	Super::BeginPlay();
    SetLevelBoundary();
    Speed = Cast<ASFGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GetSpeed();
    MoveDirection = Cast<ASFGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GetMoveDirection();
    OriginalMoveDirection = MoveDirection;
    if (GunComponent)
    {
        GunConfiguration._SingleLaserSpawnPoint = SingleLaserSpawnPoint;
        GunConfiguration._LaserSpawnPoints = LaserSpawnPoints;
        GunConfiguration._Speed = Speed;
        GunComponent->SetupGunComponent(&GunConfiguration);
    }
    if(HealthComponent != nullptr){
        HealthComponent->SetUpHealthComponent(&HealthConfiguration);
        HealthComponent->OnOutOfHealth.AddDynamic(this, &AMovingPawn::OnDeath);
    } else {
        UE_LOG(LogTemp, Error, TEXT("No Health Component Found"));
    }
    GameplayManager = Cast<AGameplayManager>(UGameplayStatics::GetActorOfClass(GetWorld(),AGameplayManager::StaticClass()));
	if(GameplayManager==nullptr){
		UE_LOG(LogTemp, Error, TEXT("GameplayManager is null"));
	}
	CurrentSpeed = Speed;
}

// Called every frame
void AMovingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if(bIsActive){
    Move();}
}
void AMovingPawn::OnDeath()
{

    DeactivatePawn();
}

void AMovingPawn::DeactivatePawn()
{
    UE_LOG(LogTemp, Error, TEXT("Pawn Deactivated %s"), *GetName());
        SetActorHiddenInGame(true);
    SetActorEnableCollision(false);
    bIsActive = false;
    GunComponent->bIsActive = false;
}

void AMovingPawn::Move()
{
    FVector MoveDelta = MoveDirection * CurrentSpeed * GetWorld()->GetDeltaSeconds();
    FVector CurrentLocation = GetActorLocation();
    AddActorWorldOffset(MoveDelta, true);
    MoveDirection = OriginalMoveDirection;
}

void AMovingPawn::SetRotation()
{
    float DesiredPitch = FMath::Clamp(MoveDirection.Z, -1.0f, 1.0f) * MaxTiltAngle / 2;
    float DesiredRoll = FMath::Clamp(MoveDirection.Y, -1.0f, 1.0f) * MaxTiltAngle;
    FRotator CurrentRotation = GetActorRotation();
    FRotator DesiredRotation = FRotator(DesiredPitch, 0.0f, DesiredRoll);
    FRotator NewRotation = FMath::RInterpTo(CurrentRotation, DesiredRotation, GetWorld()->GetDeltaSeconds(), RotationInterpSpeed);
    SetActorRotation(NewRotation);
}


void AMovingPawn::SetLevelBoundary()
{
    ASFGameModeBase* GameMode = Cast<ASFGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
    if (GameMode)
    {
        MaxBoundary = GameMode->GetMaxBoundary();
        MinBoundary = GameMode->GetMinBoundary();
    }
    
}
void AMovingPawn::LimitMovement(FVector CurrentActorLocation, FVector& MovementDelta)
{
    FVector NewLocation = CurrentActorLocation + MovementDelta;
        if (NewLocation.Z > MaxBoundary.Z || NewLocation.Z < MinBoundary.Z)
    {
        MovementDelta.Z = 0;
        MoveDirection.Z=0;
    }
    if (NewLocation.Y > MaxBoundary.Y || NewLocation.Y < MinBoundary.Y)
    {
        MovementDelta.Y = 0;
        MoveDirection.Y =0;
    }
}

void AMovingPawn::CheckIfOutOfBounds(FVector CurrentActorLocation, FVector& MovementDelta)
{
    if (CurrentActorLocation.Z > MaxBoundary.Z)
    {
        MovementDelta.Z = -100;
        MoveDirection.Z =-1;
    }
    if (CurrentActorLocation.Z < MinBoundary.Z)
    {
        MovementDelta.Z = 100;
        MoveDirection.Z =1;
    }
        if (CurrentActorLocation.Y > MaxBoundary.Y)
    {
        MovementDelta.Y = -100;
        MoveDirection.Y =-1;
    }
    if (CurrentActorLocation.Y < MinBoundary.Y)
    {
        MovementDelta.Y = 100;
        MoveDirection.Y =1;
    }
}

void AMovingPawn::ResetPawn()
{
    if(HealthComponent)
    {
        HealthComponent->SetUpHealthComponent(&HealthConfiguration);
    }
    if(GunComponent)
    {
        GunComponent->SetupGunComponent(&GunConfiguration);
        GunComponent->bIsActive = true;
    }
    bIsActive = true;
}

