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
	UPROPERTY(EditAnywhere)
	float RestoringRate;
	UPROPERTY(EditAnywhere)
	float ConsumptionRate;

	bool bShouldRestoreBoost = false;
	bool bMustRestoreBoostCompletely = false;
	bool bShouldRestoreBreak = false;
	bool bMustRestoreBreakCompletely = false;
	float CurrentBoost;
	float CurrentBreak;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool CanChangeVelocity(float &OutResource, float Rate, bool &OutResourceDepleted, bool &OutRestoringResource);
	void RestoreResource(float DeltaTime, float &OutResource, float MaxResource, float Rate, bool &OutResourceDepleted, bool &OutRestoringResource);
	void StartRestoringResource(bool &OutResourceToRestore);
private:
	UPROPERTY(EditAnywhere)
	float MaxBoost = 100;
	
	UPROPERTY(EditAnywhere)
	float MaxBreak = 100;
	


		
};
