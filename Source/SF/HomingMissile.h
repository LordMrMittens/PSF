// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HealthComponent.h"
#include "CoreMinimal.h"
#include "Projectile.h"
#include "HomingMissile.generated.h"


class AGameplayManager;
/**
 * 
 */
UCLASS()
class SF_API AHomingMissile : public AProjectile
{
	GENERATED_BODY()

	public:
		AHomingMissile();
	protected:
	 	void BeginPlay() override;
	public:
	void Tick(float DeltaTime) override;
	void SteerTowards(AActor* TargetActor) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homing")
	float HomingSpeed = 10.0f;
	private:
	AGameplayManager* GameplayManager = nullptr;
	UHealthComponent* HealthComponent = nullptr;
	UPROPERTY(EditAnywhere, Category = "Health")
	FHealthComponentConfig HealthConfiguration;
	UFUNCTION()
	void OnDeath();
	
};
