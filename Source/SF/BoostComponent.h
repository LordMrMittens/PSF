// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BoostComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SF_API UBoostComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBoostComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool CanChangeVelocity(float Resource, float Rate, bool &OutResourceBeingRestored, bool &OutResourceToRestore);
	void RestoreResource(float DeltaTime, float Resource, float MaxResource, float Rate, bool &OutResourceBeingRestored, bool &OutResourceToRestore);
	void StartRestoringResource(bool &OutResourceToRestore);
private:
	UPROPERTY(EditAnywhere)
	float MaxBoost = 100;
	float CurrentBoost;
	UPROPERTY(EditAnywhere)
	float MaxBreak = 100;
	float CurrentBreak;

	UPROPERTY(EditAnywhere)
	float RestoringRate;
	UPROPERTY(EditAnywhere)
	float ConsumptionRate;

	bool bShouldRestoreBoost = false;
	bool bMustRestoreBoostCompletely = false;
	bool bShouldRestoreBreak = false;
	bool bMustRestoreBreakCompletely = false;
		
};
