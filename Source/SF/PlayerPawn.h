// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovingPawn.h"
#include "PlayerPawn.generated.h"

struct FInputActionValue;
class AProjectile;
class UPlayerGunComponent;
class UBoostComponent;

UCLASS()
class SF_API APlayerPawn : public AMovingPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
    class UInputMappingContext* InputMapping;
	virtual void Move() override;
	virtual void SetRotation() override;


public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputDataAsset* InputActions;

	void Steer(const FInputActionValue& Value);
	

	UPlayerGunComponent* GetGunComponent() const
    {
        return GunComponent;
    }
	FVector GetVelocity() const{
		return Velocity;
	}

private:
	
	void SetUpPlayerPawn();
	void Boost();
	void FinishBoosting();
	void Break();
	void FinishBreaking();
	void CalculateVelocity();
	
	FVector PreviousLocation;

	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent* SingleLaserSpawnPoint;
	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent* DoubleLaserSpawnPointL;
	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent* DoubleLaserSpawnPointR;

	TArray<USceneComponent*> LaserSpawnPoints;
	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* MainBodyComponent;
	UPROPERTY(EditAnywhere, Category = "Components")
	UPlayerGunComponent* GunComponent;
	UPROPERTY(EditAnywhere)
	bool DoubleLaser = false;

	UPROPERTY(EditAnywhere, Category = "Components")
	UBoostComponent* BoostComponent;



	bool RecevingInput = false;

	FVector Velocity;
};
