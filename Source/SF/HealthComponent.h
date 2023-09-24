// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

USTRUCT(BlueprintType)
struct FHealthComponentConfig
{
    GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int32 MaxHealth = 10;

};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SF_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	void TakeDamage(float DamageTaken);
	void RestoreHealth(float HealthRestored);
	void SetHealth();
	void SetUpHealthComponent(FHealthComponentConfig* HealthConfig);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOutOfHealthDelegate);
	UPROPERTY(BlueprintAssignable,Category= "Health")
	FOutOfHealthDelegate OnOutOfHealth;



private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true))
	float MaxHealth;
	float CurrentHealth;






		
};
