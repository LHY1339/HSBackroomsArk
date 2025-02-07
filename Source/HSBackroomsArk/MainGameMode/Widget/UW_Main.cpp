// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_Main.h"

#include "Components/ScrollBox.h"
#include "HSBackroomsArk/Interface/IDetail.h"
#include "HSBackroomsArk/MainGameMode/MainCharacter.h"
#include "HSBackroomsArk/MainGameMode/Widget/UW_Detail.h"

void UUW_Main::FlushInteractList()
{
	if (!Character)
	{
		return;
	}
	ScrollBox_InteractList->ClearChildren();
	for (int32 i = 0; i < Character->DetailActorList.Num(); i++)
	{
		IIDetail* Interface = Cast<IIDetail>(Character->DetailActorList[i]);
		if (Interface)
		{
			if (Interface->Execute_GetCanShowDetail(Character->DetailActorList[i]))
			{
				UUW_Detail* Child = CreateWidget<UUW_Detail>(GetWorld(), DetailWidgetClass);
				Child->AddToViewport(1);
				Child->DetailActor = Character->DetailActorList[i];
				Child->Character=Character;
				ScrollBox_InteractList->AddChild(Child);
			}
		}
	}
}
