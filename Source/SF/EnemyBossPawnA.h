// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BossEnemyPawn.h"
#include "EnemyBossPawnA.generated.h"

/**
 * 
 */
UCLASS()
class SF_API AEnemyBossPawnA : public ABossEnemyPawn
{
	GENERATED_BODY()
	public:
	AEnemyBossPawnA();
	protected:
	virtual void BeginPlay() override;
	public:
	virtual void Tick(float DeltaTime) override;
	private:
		UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent *MainGunBodyMesh;
		UPROPERTY(EditAnywhere, Category = "Components")
	UGunComponent *SecondaryGunComponent;
		UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent *SecondaryGunBodyMesh;
		UPROPERTY(EditAnywhere, Category = "Guns")
	FGunComponentConfig SecondaryGunConfiguration;
		UPROPERTY(EditAnywhere, Category = "Components")
	UGunComponent *TertiaryGunComponent;
		UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent *TertiaryGunBodyMesh;
	UPROPERTY(EditAnywhere, Category = "Guns")
		FGunComponentConfig TertiaryGunConfiguration;
		
	
};
