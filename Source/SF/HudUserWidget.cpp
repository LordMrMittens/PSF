// Fill out your copyright notice in the Description page of Project Settings.


#include "HudUserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"


void UHudUserWidget::SetResourcePercent(UProgressBar *ResourceBar,float ResourcePercent)
{
    UE_LOG(LogTemp, Display, TEXT("ResourcePercent: %f"), ResourcePercent);
    ResourceBar->SetPercent(ResourcePercent);
}

void UHudUserWidget::UpdateNumberOfBombs(int NumberOfBombs)
{
    int BombIndex = NumberOfBombs;
    for (UImage* Image : BombIcons)
    {
        if (BombIndex > 0)
        {
            Image->SetOpacity(1);
            BombIndex--;
        }
        else{Image->SetOpacity(0);}
        
    }
    
}
