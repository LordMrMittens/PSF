// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "InputDataAsset.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
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
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
    Super::BeginPlay();
    OriginalMoveDirection = MoveDirection;
    SpringArmComponent = FindComponentByClass<USpringArmComponent>();
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    Move();
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
        PEI->BindAction(InputActions->FireLaser, ETriggerEvent::Started, this, &APlayerPawn::FireLasers);
    }
}

void APlayerPawn::Steer(const FInputActionValue &Value)
{
    FVector2D SteerValue = Value.Get<FVector2D>();
    MoveDirection.Z = SteerValue.Y;
    MoveDirection.Y = SteerValue.X;
}

void APlayerPawn::Move()
{
    FVector MoveDelta = MoveDirection * Speed * GetWorld()->GetDeltaSeconds();
    AddActorWorldOffset(MoveDelta, true);
    SetRotation();
    MoveDirection = OriginalMoveDirection;
}

void APlayerPawn::SetRotation()
{
    float DesiredPitch = FMath::Clamp(MoveDirection.Z, -1.0f, 1.0f) * MaxTiltAngle / 2;
    float DesiredRoll = FMath::Clamp(MoveDirection.Y, -1.0f, 1.0f) * MaxTiltAngle;

    FRotator CurrentRotation = GetActorRotation();
    FRotator DesiredRotation = FRotator(DesiredPitch, 0.0f, DesiredRoll);
    FRotator NewRotation = FMath::RInterpTo(CurrentRotation, DesiredRotation, GetWorld()->GetDeltaSeconds(), RotationInterpSpeed);

    if (SpringArmComponent)
    {
        FRotator SpringArmRotation = SpringArmComponent->GetRelativeRotation();
        SpringArmRotation.Roll *= 0.5f; // Reduce the roll rotation by 50%
        SpringArmComponent->SetRelativeRotation(SpringArmRotation);
    }
    SetActorRotation(NewRotation);
}

void APlayerPawn::FireLasers()
{
    if(DoubleLaser){
        for (USceneComponent* SpawnPoint : LaserSpawnPoints)
        {
            SpawnLaser(SpawnPoint);
        }
        
    } else {
        SpawnLaser(SingleLaserSpawnPoint);
    }

}

void APlayerPawn::SpawnLaser(USceneComponent *SpawnPoint)
{
    AProjectile *Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,
                                                                  SpawnPoint->GetComponentLocation(),
                                                                  SpawnPoint->GetComponentRotation());
    if (Projectile)
    {
        Projectile->SetOwner(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
        Projectile->SetSpeed(Speed * 4);
    }
}
