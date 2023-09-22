// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "InputDataAsset.h"
#include "SFGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerGunComponent.h"
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
    GunComponent = CreateDefaultSubobject<UPlayerGunComponent>(TEXT("Gun"));
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
    Super::BeginPlay();
    SetUpPlayerPawn();
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    CalculateVelocity();
    
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
        PEI->BindAction(InputActions->FireBombs, ETriggerEvent::Started,  GunComponent, &UGunComponent::FireBombs);
        PEI->BindAction(InputActions->Boost,  ETriggerEvent::Triggered ,this,&APlayerPawn::Boost);
        PEI->BindAction(InputActions->Boost,  ETriggerEvent::Completed ,this,&APlayerPawn::FinishBoosting);
        PEI->BindAction(InputActions->Break,  ETriggerEvent::Triggered ,this,&APlayerPawn::Break);
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
    FVector MoveDelta = MoveDirection * CurrentSpeed * GetWorld()->GetDeltaSeconds();
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

void APlayerPawn::CalculateVelocity()
{
    FVector CurrentLocation = GetActorLocation();
    Velocity = (CurrentLocation - PreviousLocation) / GetWorld()->GetDeltaSeconds();
    PreviousLocation = CurrentLocation;
}

void APlayerPawn::SetUpPlayerPawn()
{
    SpringArmComponent = FindComponentByClass<USpringArmComponent>();
    if(GunComponent){
        GunConfiguration._SingleLaserSpawnPoint = SingleLaserSpawnPoint;
        GunConfiguration._LaserSpawnPoints = LaserSpawnPoints;
        GunConfiguration._Speed = Speed;
        GunComponent->SetupGunComponent(&GunConfiguration, this);
    }
    BoostComponent = Cast<UBoostComponent>(GetComponentByClass(UBoostComponent::StaticClass()));
    if(BoostComponent != nullptr){

    } else {
        UE_LOG(LogTemp, Error, TEXT("No boost Component Found"));
    }
}

void APlayerPawn::Boost()
{
    if (BoostComponent)
    {
        if (BoostComponent->CanChangeVelocity(BoostComponent->CurrentBoost, BoostComponent->ConsumptionRate, BoostComponent->bMustRestoreBoostCompletely, BoostComponent->bShouldRestoreBoost))
        {
            CurrentSpeed = Speed * 2;
        }
        else
        {
            FinishBoosting();
        }
    }
}

void APlayerPawn::FinishBoosting()
{
    CurrentSpeed = Speed;
    if (BoostComponent)
    {
        BoostComponent->StartRestoringResource(BoostComponent->bShouldRestoreBoost);
    }
}

void APlayerPawn::Break()
{
    if (BoostComponent->CanChangeVelocity(BoostComponent->CurrentBreak, BoostComponent->ConsumptionRate, BoostComponent->bMustRestoreBreakCompletely, BoostComponent->bShouldRestoreBreak))
    {
        CurrentSpeed = Speed / 2;
    } else {
        FinishBreaking();
    }
}

void APlayerPawn::FinishBreaking()
{
    CurrentSpeed = Speed;
        if(BoostComponent){
        BoostComponent->StartRestoringResource(BoostComponent->bShouldRestoreBreak);
    }
}
