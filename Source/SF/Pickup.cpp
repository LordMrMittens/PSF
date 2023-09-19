// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"
#include "Components/CapsuleComponent.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComponent);
	MainBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainBodyComponent"));
	MainBody->SetupAttachment(CapsuleComponent);


}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	if(CapsuleComponent){
		CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnBeginOverlap);
	}
	UE_LOG(LogTemp, Error, TEXT("I Am Alive"));
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickup::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult){
	UE_LOG(LogTemp, Error, TEXT("Pickup Hit"));
}


