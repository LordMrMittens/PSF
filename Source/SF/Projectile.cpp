// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "HealthComponent.h"
#include "MovingPawn.h"
#include "GameplayManager.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MainBodyComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileBody"));
	SetRootComponent(MainBodyComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	if (MainBodyComponent)
	{
		MainBodyComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
		MainBodyComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlapStart);
	}
	GameplayManager = Cast<AGameplayManager>(UGameplayStatics::GetActorOfClass(GetWorld(),AGameplayManager::StaticClass()));
	CurrentDamage = BaseDamage;
	SetLifeSpan(LifeDuration);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();

}

void AProjectile::SetSpeed(float InputSpeed)
{
	Speed = InputSpeed;
	CurrentSpeed = Speed;
}
void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Error, TEXT("Laser Hit"));
	Destroy();
}

void AProjectile::OnOverlapStart(class UPrimitiveComponent *OverlappedComp, class AActor *OtherActor, class UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (GetOwner() == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No Owner"));
	}
	if (OtherActor != GetOwner() && OtherActor->GetOwner() != GetOwner())
	{
		UHealthComponent* HealthComponent = Cast<UHealthComponent>(OtherActor->GetComponentByClass(UHealthComponent::StaticClass()));
		if(HealthComponent != nullptr)
		{
			HealthComponent->TakeDamage(CurrentDamage);
		}
		Destroy();
	}

}

void AProjectile::SteerTowards(AActor *TargetActor)
{
	     FVector TargetLocation = TargetActor->GetActorLocation();
        FVector EnemyLocation = GetActorLocation();
        FVector TargetDirection = (TargetLocation - EnemyLocation).GetSafeNormal();
            Direction.Z += TargetDirection.Z * SteerFactor;
            Direction.Y += TargetDirection.Y * SteerFactor;
}
