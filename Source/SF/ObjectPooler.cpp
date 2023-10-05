// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPooler.h"


AActor* UObjectPooler::GetObject(FVector Location, FRotator Rotation)
{
    for (AActor* Object : ObjectPool)
    {
        UE_LOG(LogTemp, Display, TEXT("Looping Actor"));
        UE_LOG(LogTemp, Error, TEXT("Object is hidden %s"), Object->IsHidden() ? TEXT("true") : TEXT("false"));
        UE_LOG(LogTemp, Error, TEXT("Object is being destroyed %s"), Object->IsActorBeingDestroyed() ? TEXT("true") : TEXT("false"));
        if (!Object->IsActorBeingDestroyed() && Object->IsHidden())
        {
            Object->SetActorLocation(Location);
            Object->SetActorRotation(Rotation);
            Object->SetActorHiddenInGame(false);
            Object->SetActorEnableCollision(true);
            UE_LOG(LogTemp, Display, TEXT("Returning Object %s"), *Object->GetName());
            return Object;
        }
    }
    UE_LOG(LogTemp, Display, TEXT("Returning null"),);
    return nullptr;
}

void UObjectPooler::ReturnObject(AActor* Object)
{
    Object->SetActorHiddenInGame(true);
    Object->SetActorEnableCollision(false);
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
        NewObject->SetActorHiddenInGame(true);
        NewObject->SetActorEnableCollision(false);
        ObjectPool.Add(NewObject);
    }
    
}
