// Fill out your copyright notice in the Description page of Project Settings.


#include "HudUserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"


void UHudUserWidget::SetResourcePercent(UProgressBar *ResourceBar,float ResourcePercent)
{
    //health already sent as a percentage 
    // stamina needs the same
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
