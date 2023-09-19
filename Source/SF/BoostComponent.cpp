// Fill out your copyright notice in the Description page of Project Settings.


#include "BoostComponent.h"

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
	
}


// Called every frame
void UBoostComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	RestoreResource(DeltaTime, CurrentBoost, MaxBoost, RestoringRate, bMustRestoreBoostCompletely, bShouldRestoreBoost);
	RestoreResource(DeltaTime, CurrentBreak, MaxBreak, RestoringRate, bMustRestoreBreakCompletely, bShouldRestoreBreak);
	UE_LOG(LogTemp, Display, TEXT("currentBoost = %f"), CurrentBoost);
}

bool UBoostComponent::CanChangeVelocity(float &OutResource, float Rate, bool &OutResourceBeingRestored, bool &OutResourceToRestore)
{
	if (OutResourceBeingRestored == true)
	{
		return false;
	}

	if (OutResource > 0)
	{
		OutResource -= Rate * GetWorld()->GetDeltaSeconds();
		OutResourceToRestore = false;
	}
	if(OutResource <=0){
	OutResourceBeingRestored = true;
	OutResourceToRestore = true;
	}
	return OutResource > 0;
}
void UBoostComponent::StartRestoringResource(bool &OutResourceToRestore){
	OutResourceToRestore = true;
}

void UBoostComponent::RestoreResource(float DeltaTime, float &OutResource, float MaxResource, float Rate, bool &OutResourceBeingRestored, bool &OutResourceToRestore){
	if(OutResourceToRestore){
		OutResource += Rate * DeltaTime;
		if(OutResource >= MaxResource){
			OutResource =MaxResource;
			OutResourceToRestore = false;
			OutResourceBeingRestored = false;
		}
	}
}

