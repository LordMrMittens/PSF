// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Explosion.generated.h"

class USphereComponent;

UCLASS()
class SF_API AExplosion : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AExplosion();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Explosion",  meta = (AllowPrivateAccess = "true"))
    float ExplosionDuration;
	float Duration;
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Explosion",  meta = (AllowPrivateAccess = "true"))
    float TimeToMaxSize;
	    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Explosion",  meta = (AllowPrivateAccess = "true"))
    float StartSize;
	    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Explosion",  meta = (AllowPrivateAccess = "true"))
    float MaxSize;
	float SpawnTime;
	float CurrentSize;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    USphereComponent* SphereComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components",  meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MainBodyComponent;
	void SetMaxSize(float NewMaxSize) {MaxSize = NewMaxSize;}

private:




};
