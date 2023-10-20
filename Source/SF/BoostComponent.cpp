// Fill out your copyright notice in the Description page of Project Settings.


#include "BoostComponent.h"
#include "HudUserWidget.h"
#include "PlayerPawn.h"

// Sets default values for this component's properties
UBoostComponent::UBoostComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBoostComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentBoost = MaxBoost;
	CurrentBreak = MaxBreak;
	PlayerPawn = Cast<APlayerPawn>(GetOwner());
	
}


// Called every frame
void UBoostComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	RestoreResource(DeltaTime, CurrentBoost, MaxBoost, RestoringRate, bMustRestoreBoostCompletely, bShouldRestoreBoost);
	RestoreResource(DeltaTime, CurrentBreak, MaxBreak, RestoringRate, bMustRestoreBreakCompletely, bShouldRestoreBreak);
	if (PlayerPawn){
		PlayerPawn->HudUserWidget->SetResourcePercent(PlayerPawn->HudUserWidget->StaminaBar, GetCurrentBoostPercentage());
	}
}

bool UBoostComponent::CanChangeVelocity(float &OutResource, float Rate, bool &OutResourceWasDepleted, bool &OutRestoringResource)
{
	if (OutResourceWasDepleted == true)
	{
		return false;
	}

	if (OutResource > 0)
	{
		OutResource -= Rate * GetWorld()->GetDeltaSeconds();
		OutRestoringResource = false;
	}
	if(OutResource <=0){
	OutResourceWasDepleted = true;
	OutRestoringResource = true;
	}
	return OutResource > 0;
}
void UBoostComponent::StartRestoringResource(bool &OutResourceToRestore){
	OutResourceToRestore = true;
}

void UBoostComponent::RestoreResource(float DeltaTime, float &OutResource, float MaxResource, float Rate, bool &OutResourceWasDepleted, bool &OutRestoringResource){
	if(OutRestoringResource){
		OutResource += Rate * DeltaTime;
		if(OutResource >= MaxResource){
			OutResource =MaxResource;
			OutRestoringResource = false;
			OutResourceWasDepleted = false;
		}
	}
}

