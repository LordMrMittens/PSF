// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"
#include "Components/CapsuleComponent.h"
#include "PlayerPawn.h"
#include "HealthComponent.h"
#include "PlayerGunComponent.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComponent);
	MainBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainBodyComponent"));
	MainBody->SetupAttachment(CapsuleComponent);
	IconMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("IconMeshComponent"));
	IconMesh->SetupAttachment(CapsuleComponent);
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	if(CapsuleComponent){
		CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnBeginOverlap);
	}
	
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APickup::OnBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	APlayerPawn *Player = Cast<APlayerPawn>(OtherActor);
	if (Player)
	{
		UPlayerGunComponent *PlayerGunComponent = Player->GetGunComponent();
		switch (PickupType)
		{
		case EPickupType::LaserUpgrade:
			
			if (PlayerGunComponent)
			{
				PlayerGunComponent->EnhanceLasers();
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Gun Component is null"));
			}
			break;
		case EPickupType::BombPickup:
			if (PlayerGunComponent)
			{
			 PlayerGunComponent->AddBomb(1);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Gun Component is null"));
			}
			break;
		case EPickupType::RepairPickup:
			Player->HealthComponent->RestoreHealth(100);
			//repair wings if broken when wings are implemented
			break;

		default:
			EPickupType::RepairPickup;
			break;
		}
		Destroy();
	}
}
