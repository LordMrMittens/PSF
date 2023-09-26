// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Explosion.h"
#include "Explosion_Damaging.generated.h"

/**
 * 
 */
UCLASS()
class SF_API AExplosion_Damaging : public AExplosion
{
	GENERATED_BODY()

public:
AExplosion_Damaging();
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Explosion",  meta = (AllowPrivateAccess = "true"))
    float BaseDamage;

    // The actors that have already been damaged by the explosion
    TArray<AActor*> DamagedActors;
public: 
    // Called when an actor overlaps with the sphere component
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
