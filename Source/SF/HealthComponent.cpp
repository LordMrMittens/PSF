// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "HudUserWidget.h"
#include "PlayerPawn.h"

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

void UHealthComponent::UpdateHealthBar()
{
	if(GetOwner() == UGameplayStatics::GetPlayerPawn(GetWorld(),0)){
		APlayerPawn * PlayerPawn = Cast<APlayerPawn>(GetOwner());
		UHudUserWidget* UserWidget = PlayerPawn->HudUserWidget;
		if(UserWidget){
			UserWidget->SetResourcePercent(UserWidget->HealthBar,GetHealthPercentage());
			
		}
	}
}

