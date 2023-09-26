// Fill out your copyright notice in the Description page of Project Settings.


#include "Explosion.h"
#include "Components/SphereComponent.h"
#include "Components/TimelineComponent.h"

// Sets default values
AExplosion::AExplosion()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SetRootComponent(SphereComponent);
	MainBodyComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainBodyComponent"));
	MainBodyComponent->SetupAttachment(SphereComponent);

}

// Called when the game starts or when spawned
void AExplosion::BeginPlay()
{
	Super::BeginPlay();
	SetActorScale3D(FVector(StartSize));
	CurrentSize = StartSize;
	Duration = (MaxSize - StartSize) / ExplosionDuration;
}

// Called every frame
void AExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurrentSize += DeltaTime * Duration;
    SetActorScale3D(FVector(CurrentSize));

    // Destroy the explosion when it reaches its maximum scale
    if (CurrentSize >= MaxSize)
    {
        Destroy();
    }
}



