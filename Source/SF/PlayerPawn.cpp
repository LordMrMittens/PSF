// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "InputDataAsset.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
    OriginalMoveDirection = MoveDirection;

}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    Move();


}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	    // Get the player controller
    APlayerController* PC = Cast<APlayerController>(GetController());
    // Get the local player subsystem
    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());

    // Clear out existing mapping, and add our mapping
    Subsystem->ClearAllMappings();
    Subsystem->AddMappingContext(InputMapping, 0);

    UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    if( InputActions != nullptr){
// Bind the actions
    PEI->BindAction(InputActions->InputSteer, ETriggerEvent::Triggered, this, &APlayerPawn::Steer);
}
}

void APlayerPawn::Steer(const FInputActionValue& Value)
{
    FVector2D SteerValue = FVector2D::ZeroVector;
    SteerValue = Value.Get<FVector2D>();
    MoveDirection.Z = SteerValue.Y;
    MoveDirection.Y = SteerValue.X;
}

void APlayerPawn::Move()
{
    FVector CurrentLoc = GetActorLocation();
    FVector NewLocation = CurrentLoc+MoveDirection * Speed * GetWorld()->GetDeltaSeconds();
    SetActorLocation(NewLocation);
    MoveDirection = OriginalMoveDirection;
}


