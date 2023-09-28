// Fill out your copyright notice in the Description page of Project Settings.


#include "FlakGunComponent.h"
#include "GameplayManager.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerPawn.h"

UFlakGunComponent::UFlakGunComponent()
{
    
}

void UFlakGunComponent::Aim(void (UGunComponent::*FireFunctionPtr)())
{
	if (GameplayManager)
	{
		float LeadFactor = 1.0f;
		FVector PlayerLocation = GameplayManager->GetPlayerLocation();
		FVector PlayerVelocity = FVector::ZeroVector;

		APlayerPawn *PlayerPawn = GameplayManager->GetPlayerPawn();
		if (PlayerPawn)
		{
			PlayerVelocity = FVector(PlayerPawn->GetVelocity().X,0,0);  
		}
		FVector RelativePlayerLocation = PlayerLocation - GetOwner()->GetActorLocation();
		float TimeToHit = RelativePlayerLocation.Size() / (Speed * ShotSpeedMultiplier);
		LeadFactor = FMath::RandRange(ShotLeadErrorMin, ShotLeadErrorMax);
		FVector PredictedPlayerLocation = PlayerLocation + (PlayerVelocity * (TimeToHit * LeadFactor));
        PredictedPlayerLocation.Z=GameplayManager->GetPlayerLocation().Z;
		FVector GunDirection = PredictedPlayerLocation - GetOwner()->GetActorLocation();
        
		FRotator NewRotation = GunDirection.Rotation();
		if (bUsesWorldRotationWhenAiming)
		{
			SetWorldRotation(NewRotation);
		}
		else
		{
			SetRelativeRotation(NewRotation);
		}
		(this->*FireFunctionPtr)();
	} else {
		UE_LOG(LogTemp, Error, TEXT("GameplayManager is null"));
	}
}
