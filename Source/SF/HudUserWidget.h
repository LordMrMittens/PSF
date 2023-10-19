// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HudUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class SF_API UHudUserWidget : public UUserWidget
{
	GENERATED_BODY()

	public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (bindwidget) )
	class UProgressBar* HealthBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HealthPercent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (bindwidget))
	UProgressBar* StaminaBar;
	float StaminaPercent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UImage*> BombIcons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (bindwidget))
	UImage *BombIcon1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (bindwidget))
	UImage *BombIcon2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (bindwidget))
	UImage *BombIcon3;

	UFUNCTION(BlueprintCallable)
	void SetResourcePercent(UProgressBar *ResourceBar,float Resource);
	UFUNCTION(BlueprintCallable)
	void UpdateNumberOfBombs(int NumberOfBombs);
};
