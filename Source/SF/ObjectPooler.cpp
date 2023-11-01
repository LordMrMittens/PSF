// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPooler.h"
#include "MovingPawn.h"


AActor* UObjectPooler::GetObject(FVector Location, FRotator Rotation)
{
    for (AActor *Object : ObjectPool)
    {
        if (!Object->IsActorBeingDestroyed() && Object->IsHidden())
        {
            Object->SetActorLocation(Location);
            Object->SetActorRotation(Rotation);
            Object->SetActorHiddenInGame(false);
            Object->SetActorEnableCollision(true);
            ActiveObjectPool.Add(Object);
            return Object;
        }
    }
    return nullptr;
}

void UObjectPooler::ReturnObject(AActor *Object)
{
    UE_LOG(LogTemp, Display, TEXT("Object has returned"));
    Object->SetActorHiddenInGame(true);
    Object->SetActorEnableCollision(false);
    ActiveObjectPool.Remove(Object);
}

void UObjectPooler::Initialize(UWorld* World)
{
    for (int32 i = 0; i < PoolSize; i++)
    {
        if(ObjectClass == nullptr)
        {
            UE_LOG(LogTemp, Error, TEXT("Object Class is null"));
            return;
        }

        AActor* NewObject = World->SpawnActor<AActor>(ObjectClass);
        AMovingPawn* MovingPawn = Cast<AMovingPawn>(NewObject);
        if(MovingPawn)
        {
        MovingPawn->OnActorHasDeactivated.AddDynamic(this, &UObjectPooler::ReturnObject);
        }
        NewObject->SetActorHiddenInGame(true);
        NewObject->SetActorEnableCollision(false);
        ObjectPool.Add(NewObject);
    }
    
}
