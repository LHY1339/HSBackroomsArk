// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUD.h"

#include "CanvasItem.h"
#include "MainCharacter.h"
#include "Engine/Canvas.h"
#include "HSBackroomsArk/Interface/IView.h"
#include "Kismet/GameplayStatics.h"

void AMainHUD::DrawHUD()
{
	Super::DrawHUD();

	if (!Character)
	{
		Character=Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
		return;
	}
	
	__DrawView();
}

void AMainHUD::__DrawView()
{
	for (int32 i=0;i<Character->ViewActorList.Num();i++)
	{
		FVector2D ScreenPos;
		bool InScreen = UGameplayStatics::ProjectWorldToScreen(
			UGameplayStatics::GetPlayerController(GetWorld(), 0),
			Character->ViewActorList[i]->GetActorLocation(),
			ScreenPos
		);
		if (InScreen)
		{
			IIView* Interface = Cast<IIView>(Character->ViewActorList[i]);
			if (Interface)
			{
				if (Interface->Execute_GetCanView(Character->ViewActorList[i]))
				{
					UTexture2D* Tex = Interface->Execute_GetViewTexture(Character->ViewActorList[i]);
					FVector2D TexSize = Interface->Execute_GetViewTextureSize(Character->ViewActorList[i]);
					FLinearColor Color(1.0f, 1.0f, 1.0f, 1.0f);
					
					FCanvasTileItem TileItem(ScreenPos - FVector2D(TexSize / 2), Tex->Resource, FVector2D(TexSize), Color);
					TileItem.BlendMode = ESimpleElementBlendMode::SE_BLEND_Translucent;
					Canvas->DrawItem(TileItem);
				}
			}
		}
	}
}
