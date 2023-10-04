// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ObjectPooler.generated.h"

/**
 * 
 */
UCLASS()
class SF_API UObjectPooler : public UObject
{
	GENERATED_BODY()

	public:
    UFUNCTION(BlueprintCallable)
    AActor* GetObject(FVector Location, FRotator Rotation);

    UFUNCTION(BlueprintCallable)
    void ReturnObject(AActor* Object);

	UFUNCTION(BlueprintCallable)
	void Initialize(UWorld* World);
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ObjectClass;

    UPROPERTY(EditAnywhere)
    int32 PoolSize;

private:
    TArray<AActor*> ObjectPool;
	    
    
};
