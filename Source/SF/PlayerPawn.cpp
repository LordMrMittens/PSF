// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "InputDataAsset.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "GunComponent.h"
#include "BoostComponent.h"
#include "Projectile.h"

// Sets default values
APlayerPawn::APlayerPawn()
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
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
    Super::BeginPlay();
    OriginalMoveDirection = MoveDirection;
    SpringArmComponent = FindComponentByClass<USpringArmComponent>();
    if(GunComponent){
        GunComponent->SetupGunComponent(this ,Speed, -1 ,DoubleLaser, SingleLaserSpawnPoint, LaserSpawnPoints);
    }
    BoostComponent = Cast<UBoostComponent>(GetComponentByClass(UBoostComponent::StaticClass()));
    if(BoostComponent != nullptr){

    } else {
        UE_LOG(LogTemp, Error, TEXT("No boost Component Found"));
    }
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    // Get the player controller
    APlayerController *PC = Cast<APlayerController>(GetController());
    // Get the local player subsystem
    UEnhancedInputLocalPlayerSubsystem *Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());

    // Clear out existing mapping, and add our mapping
    Subsystem->ClearAllMappings();
    Subsystem->AddMappingContext(InputMapping, 0);

    UEnhancedInputComponent *PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    if (InputActions != nullptr)
    {
        // Bind the actions
        PEI->BindAction(InputActions->InputSteer, ETriggerEvent::Triggered, this, &APlayerPawn::Steer);
        PEI->BindAction(InputActions->FireLaser, ETriggerEvent::Started,  GunComponent, &UGunComponent::FireLasers);
        PEI->BindAction(InputActions->Boost,  ETriggerEvent::Started ,this,&APlayerPawn::Boost);
        PEI->BindAction(InputActions->Boost,  ETriggerEvent::Completed ,this,&APlayerPawn::FinishBoosting);
        PEI->BindAction(InputActions->Break,  ETriggerEvent::Started ,this,&APlayerPawn::Break);
        PEI->BindAction(InputActions->Break,  ETriggerEvent::Completed ,this,&APlayerPawn::FinishBreaking);
    }
}

void APlayerPawn::Steer(const FInputActionValue &Value)
{
    FVector2D SteerValue = Value.Get<FVector2D>();
    MoveDirection.Z = SteerValue.Y;
    MoveDirection.Y = SteerValue.X;
    RecevingInput = true;
}

void APlayerPawn::Move()
{
    FVector MoveDelta = MoveDirection * Speed * GetWorld()->GetDeltaSeconds();
    FVector CurrentLocation = GetActorLocation();
    LimitMovement(CurrentLocation, MoveDelta);
    CheckIfOutOfBounds(CurrentLocation, MoveDelta);
    AddActorWorldOffset(MoveDelta, true);
    SetRotation();
    MoveDirection = OriginalMoveDirection;
    RecevingInput = false;
}

void APlayerPawn::SetRotation()
{
    Super::SetRotation();
    if (SpringArmComponent)
    {
        FRotator SpringArmRotation = SpringArmComponent->GetRelativeRotation();
        SpringArmRotation.Roll *= 0.5f; // Reduce the roll rotation by 50%
        SpringArmComponent->SetRelativeRotation(SpringArmRotation);
    }
}

void APlayerPawn::LimitMovement(FVector CurrentActorLocation, FVector& MovementDelta)
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

void APlayerPawn::CheckIfOutOfBounds(FVector CurrentActorLocation, FVector& MovementDelta)
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

FVector APlayerPawn::CalculateVelocity()
{
    FVector CurrentLocation = GetActorLocation();
    FVector Velocity = (CurrentLocation - PreviousLocation) / GetWorld()->GetDeltaSeconds();

    // Update the previous location for the next frame
    PreviousLocation = CurrentLocation;

    return Velocity;
}

void APlayerPawn::Boost()
{
    UE_LOG(LogTemp, Display, TEXT("BOOOOOOST"));
    if(BoostComponent){

    }
}

void APlayerPawn::FinishBoosting()
{
    UE_LOG(LogTemp, Display, TEXT("BOOOOOOST EEEnd"));
        if(BoostComponent){
        
    }
}

void APlayerPawn::Break()
{
    UE_LOG(LogTemp, Display, TEXT("BREEEAK"));
        if(BoostComponent){
        
    }
}

void APlayerPawn::FinishBreaking()
{
    UE_LOG(LogTemp, Display, TEXT("BREEEAK end"));
        if(BoostComponent){
        
    }
}
