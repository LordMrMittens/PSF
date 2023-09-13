// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPawn.h"

// Sets default values
AMovingPawn::AMovingPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPawn::BeginPlay()
{
	Super::BeginPlay();
    OriginalMoveDirection = MoveDirection;
	
}

// Called every frame
void AMovingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMovingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMovingPawn::Move()
{
    FVector MoveDelta = MoveDirection * Speed * GetWorld()->GetDeltaSeconds();
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

