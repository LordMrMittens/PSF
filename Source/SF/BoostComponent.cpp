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
}

bool UBoostComponent::CanChangeVelocity(float Resource, float Rate, bool &OutResourceBeingRestored, bool &OutResourceToRestore)
{
	if (OutResourceBeingRestored == true)
	{
		return false;
	}

	if (Resource > 0)
	{
		Resource -= Rate * GetWorld()->GetDeltaSeconds();
		OutResourceToRestore = false;
	}
	if(Resource <=0){
	OutResourceBeingRestored = true;
	OutResourceToRestore = true;
	}
	return Resource > 0;
}
void UBoostComponent::StartRestoringResource(bool &OutResourceToRestore){
	OutResourceToRestore = true;
}

void UBoostComponent::RestoreResource(float DeltaTime, float Resource, float MaxResource, float Rate, bool &OutResourceBeingRestored, bool &OutResourceToRestore){
	if(OutResourceToRestore){
		Resource += Rate * DeltaTime;
		if(Resource >= MaxResource){
			Resource =MaxResource;
			OutResourceToRestore = false;
			OutResourceBeingRestored = false;
		}
	}
}

