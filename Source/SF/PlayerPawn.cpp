// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "InputActionValue.h"

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
	UE_LOG(LogTemp, Error, TEXT("Alive"));
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
// Bind the actions
    PEI->BindAction(InputMoveVertical, ETriggerEvent::Triggered, this, &APlayerPawn::MoveVertical);
    PEI->BindAction(InputMoveHorizontal, ETriggerEvent::Triggered, this, &APlayerPawn::MoveHorizontal);


}

void APlayerPawn::MoveVertical(const FInputActionValue& Value)
{
    FString ValueString = Value.ToString();
    UE_LOG(LogTemp, Display, TEXT("vert Value: %s"), *ValueString );
}

void APlayerPawn::MoveHorizontal(const FInputActionValue& Value)
{
    FString ValueString = Value.ToString();
    UE_LOG(LogTemp, Display, TEXT(" horz Value: %s"), *ValueString );
}

