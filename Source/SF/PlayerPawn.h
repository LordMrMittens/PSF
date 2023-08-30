// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

struct FInputActionValue;
class AProjectile;

UCLASS()
class SF_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
    class UInputMappingContext* InputMapping;



public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputDataAsset* InputActions;
	UPROPERTY(EditAnywhere)
	float Speed;
	UPROPERTY(EditAnywhere)
	FVector MoveDirection;
	FVector OriginalMoveDirection;

	UPROPERTY(EditAnywhere)
	float MaxTiltAngle;
	UPROPERTY(EditAnywhere)
	float RotationInterpSpeed;

	void Steer(const FInputActionValue& Value);

private:

	void Move();
	void SetRotation();

	UPROPERTY(EditAnywhere)
	USceneComponent* SingleLaserSpawnPoint;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MainBodyComponent;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectile> ProjectileClass;
	AProjectile *Projectile;

};
