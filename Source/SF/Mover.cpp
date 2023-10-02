// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"

// Sets default values
AMover::AMover()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMover::BeginPlay()
{
	Super::BeginPlay();
	CurrentSpeed = Speed;
}

// Called every frame
void AMover::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMover::Move()
{
	FVector LocalMoveDelta = Direction * CurrentSpeed * GetWorld()->GetDeltaSeconds();
	FTransform ActorTransform = GetActorTransform();
	FVector WorldMoveDelta = ActorTransform.TransformVectorNoScale(LocalMoveDelta);
	AddActorWorldOffset(WorldMoveDelta, true);
}

