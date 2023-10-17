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
    SetRootComponent(MainBodyComponent);
    PlayerGunComponent = CreateDefaultSubobject<UPlayerGunComponent>(TEXT("PlayerGun"));
    
    if(GunComponent){
        GunComponent->DestroyComponent();
        GunComponent->SetActive(false);
    }
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
        PEI->BindAction(InputActions->FireLaser, ETriggerEvent::Started,  PlayerGunComponent, &UGunComponent::FireLasers);
        PEI->BindAction(InputActions->FireBombs, ETriggerEvent::Started,  PlayerGunComponent, &UGunComponent::FireBombs);
        PEI->BindAction(InputActions->Boost,  ETriggerEvent::Triggered ,this,&APlayerPawn::Boost);
        PEI->BindAction(InputActions->Boost,  ETriggerEvent::Completed ,this,&APlayerPawn::FinishBoosting);
        PEI->BindAction(InputActions->Break,  ETriggerEvent::Triggered ,this,&APlayerPawn::Break);
        PEI->BindAction(InputActions->Break,  ETriggerEvent::Completed ,this,&APlayerPawn::FinishBreaking);
        //setup input from mouse, there will be a target reticule that auto centers on player when no input is being taken
        //player object attepts to steer in the direction of the reticle
        //if reticle is out of bounds then only the guns point in that direction
        //if not out of bounds then the player object will steer in that direction and guns will point forward
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
    bIsActive = true;
    SpringArmComponent = FindComponentByClass<USpringArmComponent>();
    if(PlayerGunComponent){
        GunConfiguration._SingleLaserSpawnPoint = SingleLaserSpawnPoint;
        GunConfiguration._LaserSpawnPoints = LaserSpawnPoints;
        GunConfiguration._Speed = Speed;
        PlayerGunComponent->SetupGunComponent(&GunConfiguration);
        PlayerGunComponent->bIsActive = true;
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
