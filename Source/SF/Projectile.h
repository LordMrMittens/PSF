// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Mover.h"
#include "Projectile.generated.h"

UCLASS()
class SF_API AProjectile : public AMover
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	virtual void OnOverlapStart(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetSpeed(float InputSpeed);
	UPROPERTY(EditAnywhere,BlueprintReadWrite , meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MainBodyComponent;
	UPROPERTY(EditAnywhere)
	float BaseDamage = 1;

	float CurrentDamage;
	UPROPERTY(EditAnywhere, Category = "Lifespan")
	float LifeDuration = 2.0f;
	FTimerHandle LifeTimerHandle;
	
};
