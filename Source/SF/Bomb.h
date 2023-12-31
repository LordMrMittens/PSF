// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "Bomb.generated.h"

class AExplosion_Damaging;
/**
 * 
 */
UCLASS()
class SF_API ABomb : public AProjectile
{
	GENERATED_BODY()
	public:
	ABomb();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

	virtual void OnOverlapStart(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	void Explode();
	bool bIsExploding = false;
	void SetDistanceToExplode(float Distance){DistanceToExplode = Distance;}
	void SetExplosionRadius(float Radius){ExplosionRadius = Radius;}
	FVector GetStartingPosition(){return StartingPosition;}
public:
	virtual void Tick(float DeltaTime) override;
private:

	UPROPERTY(EditAnywhere, Category = "Movement")
	float DistanceToExplode = 15000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite , meta = (AllowPrivateAccess = "true"))
	float ExplosionRadius = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite , meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AExplosion_Damaging> DamagingExplosionClass;

	FVector StartingPosition;
};
