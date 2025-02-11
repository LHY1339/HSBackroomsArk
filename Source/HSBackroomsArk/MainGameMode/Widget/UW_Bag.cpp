// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_Bag.h"

#include "UW_Main.h"
#include "Components/Image.h"
#include "HSBackroomsArk/Interface/IDetail.h"
#include "HSBackroomsArk/MainGameMode/MainCharacter.h"

void UUW_Bag::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (MainWidget->Character->BagList[BagIndex])
	{
		IIDetail* Interface=Cast<IIDetail>(MainWidget->Character->BagList[BagIndex]);
		if (Interface)
		{
			FSlateBrush Brush;
			Brush.SetResourceObject(Interface->Execute_GetDetailTexture(MainWidget->Character->BagList[BagIndex]));
			Image_Icon->SetBrush(Brush);
		}
		if (MainWidget->Character->BagList[BagIndex]==MainWidget->Character->HoldAsset)
		{
			Image_Icon->SetRenderOpacity(1.0f);
			Image_Icon->SetRenderScale(FVector2D(1.2,1.2));
		}
		else
		{
			Image_Icon->SetRenderOpacity(0.5f);
			Image_Icon->SetRenderScale(FVector2D(0.8,0.8));
		}
	}
	else
	{
		Image_Icon->SetRenderOpacity(0.0f);
	}
}
