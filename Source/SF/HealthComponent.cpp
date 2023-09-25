// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	
}

void UHealthComponent::TakeDamage(float DamageTaken){
CurrentHealth -= DamageTaken;
UE_LOG(LogTemp, Display, TEXT("Damage Taken: %f, currenthealth %f"), DamageTaken, CurrentHealth);
if(CurrentHealth <= 0){
	OnOutOfHealth.Broadcast();
}
}


void UHealthComponent::RestoreHealth(float HealthRestored){
CurrentHealth += HealthRestored;
if(CurrentHealth > MaxHealth){
	CurrentHealth = MaxHealth;
}
}

void UHealthComponent::SetHealth(){
	CurrentHealth = MaxHealth;
}

void UHealthComponent::SetUpHealthComponent(FHealthComponentConfig* HealthConfig){
MaxHealth = HealthConfig->MaxHealth;
SetHealth();
}

